/*
  ╦ ╦  ╔═╗  ╔╗╔  ╔╦╗  ╦    ╔═╗  ╦═╗
  ╠═╣  ╠═╣  ║║║   ║║  ║    ║╣   ╠╦╝
  ╩ ╩  ╩ ╩  ╝╚╝  ═╩╝  ╩═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _HANDLER_H_
#define _HANDLER_H_

  #include <stdbool.h>
  #include <sys/epoll.h>
  #include <sys/types.h>

  #include "../../infrastructure/logging/logging.h"

  #ifdef NO_TIMEOUT
    #define NO_TIMEOUT
  #endif

  typedef struct handler {
    // Epoll related
    struct epoll_event* events;
    struct epoll_event poll;
    ssize_t ep_fd;

    // Constraints
    ssize_t listeners; // Avoid hang having listeners > max_events
    ssize_t max_events;
    ssize_t timeout;
  } handler;

  /* Constructor of the handler */
  handler* init_handler(const ssize_t * const, const ssize_t, const ssize_t);

  /* Desstructor of the handler */
  void destroy_handler(handler*);

  /* Wait for events */
  ssize_t handler_await(handler*);

  /* Register new fd */
  bool handler_add_listener(handler* const, const ssize_t* const);

  /* Remove fd */
  bool handler_remove_listener(handler* const, const ssize_t* const);

  /* Handle close */
  void handle_close(const ssize_t* const);

  /* Handle disconnect */
  void handle_disconnect(handler* const, const ssize_t* const);


#endif
