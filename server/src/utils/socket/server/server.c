/*
  ╦ ╦  ┌┬┐  ┬  ┬    ┌─┐
  ║ ║   │   │  │    └─┐
  ╚═╝   ┴   ┴  ┴─┘  └─┘
  Autori:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

// Global headers
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Personal headers
#include "server.h"

#define _m(type, format, ...) _msgcategory(type, "SERVER", format, ##__VA_ARGS__)
#define _mth(type, format, ...) _msgcategory(type, "SERV_TH", format, ##__VA_ARGS__)

volatile sig_atomic_t persist = 1;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock_condition = PTHREAD_MUTEX_INITIALIZER;

void serve_disconnect(server* s, size_t* const index);

void handle_interrupt(int sig){
	(void)sig;
	pthread_cond_signal(&cond1); 
	persist = 0; 
}

void setup_signals(){
  struct sigaction sa;

  sa.sa_handler = handle_interrupt;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  if(sigaction(SIGINT, &sa, NULL) == -1){
    _msgfatal("[SIG] Error on signal setup!");
    perror("sigaction: ");
    exit(errno);
  }
}

server* server_init(uint port){
  unsigned int use_port = !port ? DEFAULT_PORT : port;

  server* s = malloc(sizeof(struct server));

  // Socket creation
  s ->socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (s -> socket < 0){
    _m(_msgfatal, "Failed to create socket!"); perror("socket: "); exit(errno);
  }
  _m(_msginfo, "Socket <%ld> created!", s ->socket);

  /* Socket options (Set socket as reusable) */
  if(setsockopt(s->socket, SOL_SOCKET, SO_REUSEADDR, (int[]) { 1 }, sizeof(int[1]))) {
    _m(_msgfatal, "Could not change socket settings"); perror("setsockopt: "); exit(errno);
  }

  _m(_msginfo, "Socket <%ld> set as resuable!", s->socket);

  // Socket binding

  // Zeroing the transport as suggested by IEEE (https://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html) using the bzero function (from <strings.h>)
  bzero(&s ->transport, sizeof(s->transport));

  /**
     transport configuration (sockaddr_in)
  */

  /*
    NB: 
    AF_INET = Address Format, Internet = IP Addresses
    PF_INET = Packet Format, Internet = IP, TCP/IP or UDP/IP
  */
  s -> transport.sin_family = AF_INET;

  /*
    Set port number, using htons function to use proper byte order
    We are using htons to convert PORT to a "netwrok byte order"
  */
  s ->transport.sin_port = htons(use_port);

  /* Make the server listening to any interfaces in order to make it available on the network */
  s ->transport.sin_addr.s_addr = htonl(INADDR_ANY);


  /**
     Socket Binding
     The INADDR_ANY binding does not generate a random IP address
     It maps the socket to all available interfaces (which on a server for obvious reasons is something strongly desired),
     and not just localhost.
  */

  if(bind(s->socket,(struct sockaddr*)&s->transport, sizeof(s->transport)) != 0) {
    _m(_msgfatal, "Could not bind the server!"); perror("bind: "); exit(errno);
  }
  _m(_msginfo, "[SERVER] Server binded to socket <%d>!", s->socket);

  // Socket listening
  if(listen(s->socket, MAX_CLIENTS_IN_QUEUE) != 0){
    _m(_msgfatal, "[SERVER] Could not start listening"); perror("listen: "); exit(errno); 
  }
  _m(_msgevent, "Server ready and it is listening for new clients on port: %d!", use_port);

  s->handler = handler_init(&s->socket, MAX_CLIENTS_ACCEPTANCE, SERVER_POLL_TIMER);
  s->conn_count = 0;

  // Spawn threads
  _mth(_msginfo, "Spawing threads helpers...");


  _mth(_msginfo, "Done!");
  _m(_msginfo, "Server ready, please use server_loop");

  return s;
}

void server_kill(server* s){
  _m(_msginfo, "Shutting down the server as requested");

  // Disconnect and handle users 
  //static char msg_disconnect[]	= "\n[SERVER] Server is shutting down... Goodbye!\n";
  while(s->conn_count){
    s->conn_count--;
    _m(_msginfo, "Disconnetting user %ld", s->conn_count);
  }
  close(s->socket);
  _m(_msgevent, "Goodbye!");
  free(s);
}

bool _refuse_connection(server* s){
  static char message[] = "Server connection queue is full! Please try again later";
  static const size_t msg_lenght = sizeof(message);

  ssize_t socket;
  struct sockaddr_in transport;
  socklen_t len = sizeof(transport);

  // Check accept status
  if ((socket = accept(s->socket, (struct sockaddr*) & transport, & len)) == -1){
    _m(_msgwarn, "accept failed!");
    perror("accept: ");
    close(socket);
    return false;
  }
  wrap_send(socket, message, msg_lenght, 0);
  _m(_msgevent, "Refusing sock client <%ld> from <" IPV4_ADDRESS_FORMAT "> as the server connection queue is full", socket, IPV4(transport.sin_addr.s_addr));

  close(socket);
  return true;
}