/*
  ╔═╗  ╔═╗  ╦═╗    ╦  ╦    ╔═╗  ╦═╗
  ╚═╗  ║╣   ╠╦╝    ╚╗╔╝    ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╩╚═     ╚╝     ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _SERVER_H_
#define _SERVER_H_

  #include <arpa/inet.h>
  #include "../../helpers/pool/thread_pool.h"

  #ifndef TIMEOUT_CONNECTION_S
      #define TIMEOUT_CONNECTION_S 20.0f
  #endif

  typedef enum connection_status { NEW, ALIVE, DEAD } connection_status;

  /* Server */
  typedef struct server {
    ssize_t socket;
    struct sockaddr_in transport;
    size_t conn_count;
    thread_pool_t* pool;
  } server;

  server* init_server(unsigned int, const size_t);
  void destroy_server(server*);
  void server_loop(server*);
#endif
