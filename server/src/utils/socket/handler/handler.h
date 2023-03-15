#ifndef InfoPoint_Handler
#define InfoPoint_Handler

  #include "sys/types.h"
  #include <sys/epoll.h>
  #include <stdbool.h>
  #include "../../common/utils.h"

  #ifndef NO_TIMEOUT
	  #define NO_TIMEOUT -1
  #endif

  typedef struct handler {
    // Details about epoll
    struct epoll_event *events;
    struct epoll_event poll;
    // Epoll fd
    ssize_t epfd;

    // Listener limit (avoid n° listener > n° of events)
    ssize_t listeners;

    // Handler constraints
    ssize_t max_events;
    ssize_t timeout;

  } handler;

  // Handler functions
  handler* handler_init(const ssize_t * const, const ssize_t, const ssize_t);
  void handler_kill(handler*);
  ssize_t handler_await(handler *h);	
  bool handler_add_listener(handler * const, const ssize_t * const);
  bool handler_remove_listener(handler * const, const ssize_t * const);
  void handler_close(const ssize_t * const socket);
  void handler_disconnect(handler * const, const ssize_t * const);

#endif
