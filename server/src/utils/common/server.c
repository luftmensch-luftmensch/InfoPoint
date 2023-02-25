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
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <strings.h>

// Personal headers
#include "netinet/in.h"
#include "server.h"
#include "sys/socket.h"
#include "utils.h"

#define _m(type, format, ...) _msgcategory(type, "SERVER", format, ##__VA_ARGS__)
#define _mth(type, format, ...) _msgcategory(type, "SERV_TH", format, ##__VA_ARGS__)

int check(int expr, const char* msg){
  if(expr == SOCKET_ERROR){
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return expr;
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

  // Socket options

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

  // TODO: SETUP handler
  _mth(_msginfo, "Done!");
  _m(_msginfo, "Server reade, please use server_loop");

  return s;
}

void server_kill(server* s){
  _m(_msginfo, "Shutting down the server as requested");

  // Disconnect and handle users 
  static char msg_disconnect[]	= "\n[SERVER] Server is shutting down... Goodbye!\n";
  while(s->conn_count){
    s->conn_count--;
    _m(_msginfo, "Disconnetting user %ld", s->conn_count);
  }
  close(s->socket);
  _m(_msgevent, "Goodbye!");
  free(s);
}
