/*
  ╔═╗  ╔═╗  ╦═╗    ╦  ╦    ╔═╗  ╦═╗
  ╚═╗  ║╣   ╠╦╝    ╚╗╔╝    ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╩╚═     ╚╝     ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "server.h"

#include "../message/message.h"
#include "../../helpers/logging/logging.h"
#include "../../helpers/handler/signal_handler.h"


#define _m(type, format, ...) _msgcategory(type, " SERVER ", format __VA_OPT__(,) __VA_ARGS__)

/* Control switch for gracefully shutdown (NB: This variable has to be volative!) */
volatile sig_atomic_t _keep_alive = 1;

/* Helper function for signal handler */
static void handle_interrupt();

/* Helpers functions */
bool _serve_new_conn(server*);
bool _refuse_conn(server*);

server* init_server(unsigned int port, const size_t max_clients, const size_t max_workers, char* username, char* password, char* host, char* database_name){
  // Allocate memory for the newly created server
  server* s = malloc(sizeof(struct server));
  if (s == NULL) {
    _m(_msgfatal, "[%s] (%s) Failed to allocate enought space for the server! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    return NULL;
  }

  // Database Handler setup
  s->handler = init_handler(username, password, host, database_name);
  if (s->handler == NULL) {
    _m(_msgfatal, "[%s] (%s) Failed to allocate enought space for the server->handler! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    return NULL;
  }

  // Define type of socket
  /*
    Define the type of the socket:
    + AF_INET -> IP v4;
    * SOCK_STREAM, SOCK_NONBLOCK -> We are going to use a non blocking TCP socket 
    * 0 -> Automatic protocol Type
  */
  s->socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

  if (s->socket < 0) { // Check if the call socket was sussesfull
    _m(_msgfatal, "[%s] (%s) Failed to connect socket! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    perror("socket: ");
    exit(errno);
  }
  _m(_msginfo, "[%s] (%s) Socket <%ld> created!", __FILE_NAME__, __func__, s ->socket);

  /* Socket options (Set socket as reusable) */
  if(setsockopt(s->socket, SOL_SOCKET, SO_REUSEADDR, (int[]) { 1 }, sizeof(int[1]))) {
    _m(_msgfatal, "Could not change socket settings! Cause: %s", strerror(errno));
    perror("setsockopt: ");
    exit(errno);
  }
  _m(_msginfo, "[%s] (%s) Socket <%ld> set as reusable!", __FILE_NAME__, __func__, s->socket);

  // Zeroing the transport as suggested by IEEE (https://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html) using memset
  memset(&s->transport, 0, sizeof(s->transport));

  /*
	transport configuration
    NB: 
    AF_INET = Address Format, Internet = IP Addresses
    PF_INET = Packet Format, Internet = IP, TCP/IP or UDP/IP
  */
  s -> transport.sin_family = AF_INET;

  /*
    Set port number, using htons function to use proper byte order
    We are using htons to convert PORT to a "netwrok byte order"
  */
  s ->transport.sin_port = htons(port);

  /* Make the server listening to any interfaces in order to make it available on the network */
  s ->transport.sin_addr.s_addr = htonl(INADDR_ANY);

  /**
     Socket Binding
     The INADDR_ANY binding does not generate a random IP address
     It maps the socket to all available interfaces (which on a server for obvious reasons is something strongly desired),
     and not just localhost.
  */
  if(bind(s->socket,(struct sockaddr*)&s->transport, sizeof(s->transport)) != 0) {
    _m(_msgfatal, "[%s] (%s) Could not bind the server! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    perror("bind: ");
  }
  _m(_msginfo, "[%s] (%s) Server binded to socket <%d>!", __FILE_NAME__, __func__, s->socket);

  // Socket listening
  if(listen(s->socket, max_clients) != 0){
    _m(_msgfatal, "[%s] (%s) Could not start listening! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    perror("listen: ");
    exit(errno); 
  }
  _m(_msgevent, "[%s] (%s) Server ready and it is listening for new clients on port: %d!", __FILE_NAME__, __func__, port);

  s->conn_count = 0;

  s->pool = init_thread_pool(max_workers);
  if (s->pool == NULL)  {
    _m(_msgfatal, "[%s] (%s) Failed to allocate enought space for the server->pool! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    return NULL;
  }
  
  return s;
}

void destroy_server(server* s) {
  _m(_msginfo, "[%s] (%s) Shutting down the server <%ld> as requested", __FILE_NAME__, __func__, s->socket);

  // static char msg_notice[] = "\n[SERVER] Server is shutting down... Goodbye!\n";
  while(s->conn_count--) {
    s->conn_count--;
    _m(_msgdebug, "[%s] (%s) Disconnecting client %ld", __FILE_NAME__, __func__, s->conn_count);
    // msg_send(s->connections[s->conn_count].client->fd, msg_notice, strlen(msg_notice), 0);
    // free(s->connections[s->conn_count].client);
  }

  close(s->socket);
  // Stopping and destroying the thread pool

  _m(_msgevent, "[%s] (%s) Goodbye!", __FILE_NAME__, __func__);

  destroy_handler(s->handler);
  destroy_thread_pool(s->pool);
  free(s);
}

void server_loop(server* s) {
  _m(_msgevent, "[%s] (%s) Server is now setupping signals in order to get gracefully shutdown! (To make a hard shutdown kill pid n° %d)", __FILE_NAME__, __func__, getpid());
  setup_signals(SIGINT, handle_interrupt);

  _m(_msgevent, "[%s] (%s) Server is now entering server_loop waiting for new events!", __FILE_NAME__, __func__);

  while(_keep_alive) {

  }
}


bool _serve_new_conn(server* s) {
  ssize_t socket;
  struct sockaddr_in transport;
  socklen_t len = sizeof(transport);

  /* Accept a new connection */
  if ((socket = accept(s->socket, (struct sockaddr*) &transport, &len) == -1)) {
    _m(_msgwarn, "[%s] (%s) Failed on accept()! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    perror("accept: ");
    close(socket);
    return false;
  }

  _m(_msgevent, "[%s] (%s) Received connection request <%ld> from <" IPV4_ADDRESS_FORMAT ">", __FILE_NAME__, __func__, socket, IPV4(transport.sin_addr.s_addr));

  /* Insert the new connection fd into the server->thread_pool */
  bool status = submit_task(s->pool, (void*) socket);

  return status;
}

bool _refuse_conn(server* s) {
  static char msg[] = "Sorry, server is shutting down!\nPlease, try later!\n";
  static const size_t msg_length = sizeof(msg);

  ssize_t socket;
  struct sockaddr_in transport;
  socklen_t len = sizeof(transport);

  if ((socket = accept(s->socket, (struct sockaddr*) &transport, &len) == -1)) {
    _m(_msgwarn, "[%s] (%s) Failed on accept()! Cause: %s", __FILE_NAME__, __func__, strerror(errno));
    perror("accept: ");
    close(socket);
    return false;
  }

  msg_send(socket, msg, msg_length, 0);

  _m(_msgevent, "[%s] (%s) Refusing socket <%ld> from <" IPV4_ADDRESS_FORMAT "> as the server connection queue is full!", __FILE_NAME__, __func__, socket, IPV4(transport.sin_addr.s_addr));

  // Close socket
  close(socket);
  return true;
}


static void handle_interrupt(int signal) {
  // Ignore the value of the signal -> We know that if the signal is catched the server is asked to shutdown
  (void) signal;
  _m(_msgevent, "[%s] (%s) Server is shutting down... Goodbye!", __FILE_NAME__, __func__, signal);
  _keep_alive = 0;
}
