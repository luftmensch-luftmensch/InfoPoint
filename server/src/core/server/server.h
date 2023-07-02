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
  #include "../pool/thread_pool.h"
  #include "../database/database.h"

  typedef enum connection_status { NEW, ALIVE, DEAD } connection_status;

  /* Server structure */
  typedef struct server {
    ssize_t socket;
    struct sockaddr_in transport;
    size_t conn_count;
    db_handler* handler;
    thread_pool* pool;
  } server;

  server* init_server(unsigned int, const size_t, const size_t, char*, char*, char*, char*);
  void destroy_server(server*);
  void server_loop(server*);
#endif
