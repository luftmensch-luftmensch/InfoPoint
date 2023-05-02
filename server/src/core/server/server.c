/*
  ╔═╗  ╔═╗  ╦═╗    ╦  ╦    ╔═╗  ╦═╗
  ╚═╗  ║╣   ╠╦╝    ╚╗╔╝    ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╩╚═     ╚╝     ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include "server.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _m(type, format, ...) _msgcategory(type, "SERVER", format, ##__VA_ARGS__)


//static int load_server_config(char* file_name);

server* init_server(unsigned int port, const size_t max_workers){
  unsigned int use_port = !port ? DEFAULT_PORT : port;
  _m(_msgevent, "%d", max_workers);

  // Allocate mem for the newly created server
  server* s = malloc(sizeof(struct server));

  // Define type of socket
  /*
    Define the type of the socket:
    + AF_INET -> IP v4;
    * SOCK_STREAM, SOCK_NONBLOCK -> We are going to use a non blocking TCP socket 
    * 0 -> Automatic protocol Type
  */
  s->socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

  if (s->socket < 0) { // Check if the call socket was sussesfull
    _m(_msgfatal, "Failed to connect socket!");
    perror("socket: ");
    exit(errno);
  }
  _m(_msginfo, "Socket <%ld> created!", s ->socket);

  /* Socket options (Set socket as reusable) */
  if(setsockopt(s->socket, SOL_SOCKET, SO_REUSEADDR, (int[]) { 1 }, sizeof(int[1]))) {
    _m(_msgfatal, "Could not change socket settings"); perror("setsockopt: "); exit(errno);
  }
  _m(_msginfo, "Socket <%ld> set as resuable!", s->socket);

  /* Binding */
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

  // Handler setup
  s->handler = init_handler(&s->socket, MAX_CLIENTS_ACCEPTANCE, SERVER_POLL_TIMER);

  s->conn_count = 0;

  // Thread pool setup
  
  _m(_msginfo, "Server ready!");
  return s;
}


void destroy_server(server* s) {
  _m(_msginfo, "Shutting down the server as requested");

  static char msg_notice[] = "\n[SERVER] Server is shutting down... Goodbye!\n";
  while(s->conn_count--) {
    s->conn_count--;
    _m(_msgdebug, "Disconnecting client %ld", s->conn_count);
    msg_send(s->connections[s->conn_count].client->fd, msg_notice, strlen(msg_notice), 0);
    free(s->connections[s->conn_count].client);
  }

  close(s->socket);
  // Destroying and closing handler
  destroy_handler(s->handler);
  free(s->handler);

  // Stopping and destroying the thread pool

  _m(_msgevent, "Goodbye!");
  free(s);
}
