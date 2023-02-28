#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "handler.h"
#include "../common/utils.h"
#include "sys/epoll.h"

#define _m(type, format, ...) _msgcategory(type, "HANDLER", format, ##__VA_ARGS__)

handler* handler_init(const ssize_t * const socket, const ssize_t max_events, const ssize_t timeout){
  handler *h = malloc(sizeof(handler));
  // Poll Event setup for the server socket
  /* Creates the epoll event (return an fd referring to the new epoll instance) */
  h-> epfd = epoll_create1(0);

  h-> poll.events = EPOLLIN;  // The associated file is available for read operations.
  h-> poll.data.fd = *socket; // User data fd
  h-> max_events = max_events;
  h-> timeout = timeout;
  h->listeners = 0;
  h->events = malloc(sizeof(struct epoll_event) * max_events);

  /**
     epoll_ctl() is used to  to add, modify, or remove entries in the
     interest list of the epoll(7) instance referred to by the file
     descriptor epfd.  It requests that the operation op be performed
     for the target file descriptor, fd.

     with EPOLL_CTL_ADD we are adding an entry to the interest list of the epoll file descriptor
  */
  if (epoll_ctl(h->epfd, EPOLL_CTL_ADD, *socket, &h ->poll) == -1){
    _m(_msgfatal, "Cannot setup the handler");
    perror("epoll_ctl: ");
    exit(EXIT_FAILURE);
  }
  _m(_msginfo, "Handler setup completed!");
  return h;
}

void handler_kill(handler *h){
  free(h->events);
  _m(_msgevent, "Handler was terminated!");
}

ssize_t handler_await(handler *h){
  // Wait for an I/O event on an epoll file descriptor
  return epoll_wait(h->epfd, h->events, h->max_events, h->timeout);
}

bool handler_add_listener(handler* const h, const ssize_t* const socket){
  assert(h-> listeners < h -> max_events);

  struct epoll_event event;
  /**
     Sets the events to:
     + EPOLLIN -> The associated file is available for read operations
     + EPOLLET -> Requests edge-triggered notification for the associated file descriptor.
		  The default behavior for epoll is level-triggered
  */
  event.events = EPOLLIN | EPOLLET;
  event.data.fd = *socket;

  // Report the status about the operation
  if (epoll_ctl(h->epfd, EPOLL_CTL_ADD, *socket, &event) == -1){
    _m(_msgwarn, "epoll_ctl add failed!");
    perror("epoll_ctl: ");
    return false;
  }
  return true;
}

bool handler_remove_listener(handler* const h, const ssize_t* const socket){
  assert(!h->listeners);
  // Report the status about the operation

  if (epoll_ctl(h->epfd, EPOLL_CTL_DEL, *socket, NULL) == -1){
    _m(_msgwarn, "epoll_ctl del failed!");
    perror("epoll_ctl: ");
    return false;
  }
  _m(_msgdebug, "Removed [&%ld] listener!", *socket);
  return true;
}

void handler_close(const ssize_t* const socket){
  // Close the socket
  _m(_msginfo, "Client %ld disconnected!", *socket);
  close(*socket);
}

void handler_disconnect(handler* const h, const ssize_t* const socket){
  // In case we cannot remove the listener
  if(!handler_remove_listener(h, socket))
    exit(errno);
  handler_close(socket);
}
