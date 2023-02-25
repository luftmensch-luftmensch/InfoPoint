#ifndef InfoPoint_Server
#define InfoPoint_Server

#include <sys/types.h>
#include <arpa/inet.h>

  #define SOCKET_ERROR (-1)
  /* Error handler for `socket`, `bind`, `listen`, `accept` e `read` functions (the return values in case of an error is always -1) */
  int check(int expr, const char *msg);

  // Constants
  #ifndef DEFAULT_PORT
    #define DEFAULT_PORT 9090
  #endif

  #ifndef MAX_CLIENTS_IN_QUEUE
	  #define MAX_CLIENTS_IN_QUEUE 100
  #endif

  // Server Struct
  typedef struct server {
    // Details about server
    ssize_t socket;
    struct sockaddr_in transport;

  } server;

  // Server function
  server* server_init(uint port);
  void server_kill(server*);
  void server_loop(server*);


#endif
