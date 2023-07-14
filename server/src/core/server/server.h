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

  #ifndef IPV4_ADDRESS_FORMAT
     #define IPV4_ADDRESS_FORMAT "%d.%d.%d.%d"
  #endif

  #define IPV4(IP) \
      (IP & 0x000000ff) >> 0, \
      (IP & 0x0000ff00) >> 8, \
      (IP & 0x00ff0000) >> 16,\
      (IP & 0xff000000) >> 24 \

  /* Server structure */
  typedef struct server {
    ssize_t socket;
    struct sockaddr_in transport;
    size_t conn_count;
    thread_pool* pool;
  } server;

  server* init_server(unsigned int, const size_t, const size_t, char*, char*, char*, char*);
  void destroy_server(server*);
  void server_loop(server*);
#endif
