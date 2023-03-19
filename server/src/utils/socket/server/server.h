#ifndef InfoPoint_Server
#define InfoPoint_Server

#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <pthread.h>

// #include "bits/types/struct_timeval.h"

// Personal headers
#include "../../common/utils.h"
#include "../payload.h"
#include "../handler/handler.h"
#include "../wrapper/wrapper.h"

  #define SOCKET_ERROR (-1)
  extern volatile sig_atomic_t persist;
  extern pthread_cond_t cond1;
  extern pthread_mutex_t lock_condition;

  // Constants
  #ifndef DEFAULT_PORT
    #define DEFAULT_PORT 9090
  #endif

  #ifndef MAX_CLIENTS_IN_QUEUE
	  #define MAX_CLIENTS_IN_QUEUE 100
  #endif

  #ifndef MAX_CLIENTS_ACCEPTANCE
	  #define MAX_CLIENTS_ACCEPTANCE 20
  #endif

  #ifndef SERVER_POLL_TIMER
	  #define SERVER_POLL_TIMER 1000 
  #endif


  #ifndef SERV_COMM_BUFFER_SZ
	  #define SERV_COMM_BUFFER_SZ 256
  #endif

  enum conn_status{ NEW, DEAD };

  // Server Struct
  typedef struct server {
    // Details about server
    ssize_t socket;
    struct sockaddr_in transport;

    // Handler
    handler* handler;

    // Thread pool
    pthread_t thread_pool;

    struct connection {
      client* client;
      enum conn_status status;
      bool was_updated;
      struct timeval tm;
    } conn_list[MAX_CLIENTS_ACCEPTANCE];

    size_t conn_count;

    // Communication buffer
    char communication_buf[SERV_COMM_BUFFER_SZ + 1];

  } server;

  // Server function
  server* server_init(uint port);
  void server_kill(server*);
  void server_loop(server*);

  // Signals setup for the server
  void handle_interrupt(int sig);
  void setup_signals();

#endif
