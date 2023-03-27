/*
  ╔═╗  ╔═╗  ╦═╗    ╦  ╦    ╔═╗  ╦═╗
  ╚═╗  ║╣   ╠╦╝    ╚╗╔╝    ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╩╚═     ╚╝     ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _SERVER_H_
#define _SERVER_H_

  #include <stdio.h>
  #include <stdbool.h>
  #include <strings.h>
  #include <errno.h>

  #include <sys/socket.h>
  #include <sys/time.h>
  #include <sys/types.h>

  #include <arpa/inet.h>
  #include <netinet/in.h>

  #include "../pool/thread_pool.h"
  #include "../handler/handler.h"
  #include "../message/message.h"
  #include "../payload/client/client.h"
  #include "../../infrastructure/logging/logging.h"

  #ifndef DEFAULT_PORT
      #define DEFAULT_PORT 60020
  #endif

  #ifndef SERVER_POLL_TIMER
      #define SERVER_POLL_TIMER 1000 
  #endif

  #ifndef MAX_ROOMS_PER_SERVER
      #define MAX_ROOMS_PER_SERVER 32 
  #endif

  #ifndef MAX_CLIENTS_IN_QUEUE
      #define MAX_CLIENTS_IN_QUEUE 4
  #endif

  #ifndef MAX_CLIENTS_ACCEPTANCE
      #define MAX_CLIENTS_ACCEPTANCE 1000
  #endif

  #ifndef TIMEOUT_CONNECTION_S
      #define TIMEOUT_CONNECTION_S 20.0f
  #endif

  #ifndef MAX_IDLE_TIMEOUT
    #define MAX_IDLE_TIMEOUT 0 // Default client timeout -> infinite
  #endif

  /* Config file configuration */
  #ifndef MAX_CONFIG_LINE
    #define MAX_CONFIG_LINE 1024
  #endif


  #ifndef POOL_SIZE
      #define POOL_SIZE 10
  #endif

  #ifndef SERV_COMM_BUFFER_SZ
      #define SERV_COMM_BUFFER_SZ 256
  #endif

  typedef enum connection_status { NEW, ALIVE, DEAD } connection_status;

  /* Server */
  typedef struct server {
    // Server details
    ssize_t socket;
    struct sockaddr_in transport;

    // Handler
    handler* handler;

    // pthread_t* pool;
    struct thread_pool pool;

    struct connection {
      client* client;
      connection_status status;
      bool was_updated;
      struct timeval tm;
    } connections[MAX_CLIENTS_ACCEPTANCE];

    size_t conn_count;
  } server;

  server* init_server(unsigned int, const size_t);
  void destroy_server(server*);
  void server_loop(server*);
#endif
