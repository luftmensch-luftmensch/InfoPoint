/*
  ╦ ╦  ╔═╗  ╔╗╔  ╔╦╗  ╦    ╔═╗  ╦═╗
  ╠═╣  ╠═╣  ║║║   ║║  ║    ║╣   ╠╦╝
  ╩ ╩  ╩ ╩  ╝╚╝  ═╩╝  ╩═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "handler.h"

#define _m(type, format, ...) _msgcategory(type, "HANDLER", format, ##__VA_ARGS__)


handler* init_handler(const ssize_t* const fd, const ssize_t max_events, const ssize_t timeout) {
  _m(_msgevent, "Initializing handler as requested!");

  handler* h = malloc(sizeof(struct handler));

  // Handler field initialization
  h->ep_fd = epoll_create1(0);
  h->poll.events = EPOLLIN;
  h->poll.data.fd = *fd;
  h->max_events = max_events;
  h->timeout = timeout;
  h->events = malloc(sizeof(struct epoll_event) * max_events);

  if(epoll_ctl(h->ep_fd, EPOLL_CTL_ADD, *fd, &h->poll) == -1) {
    _m(_msgfatal, "Could not setup the handler!!");
    perror("epoll_ctl: ");
    exit(errno);
  }
  _m(_msginfo, "Handler has been setup!");
  return h;
}

void destroy_handler(handler* h) {
  free(h->events);
  _m(_msgevent, "Handler has been shutted down!");
}

ssize_t handler_await(handler* h) {
  // Poll for new events
  return epoll_wait(h->ep_fd, h->events, h->max_events, h->timeout);
}

bool handler_add_listener(handler* const h, const ssize_t * const fd) {
  assert(h->listeners < h->max_events);

  struct epoll_event event;
  event.events = EPOLLIN | EPOLLET;
  event.data.fd = *fd;

  // Report the status of epoll_ctl (control interface for EP_D)
  if (epoll_ctl(h->ep_fd, EPOLL_CTL_ADD, *fd, &event) == -1) {
    _m(_msgfatal, "Failed to add event to handler!");
    perror("epoll_ctl: ");
    return false;
  }
  _m(_msgdebug, "Added [&%ld] listener", *fd);
  return true;
}

bool handler_remove_listener(handler* const h, const ssize_t* const fd) {
  assert(!h->listeners);

  // Report the status of epoll_ctl
  if (epoll_ctl(h->ep_fd, EPOLL_CTL_DEL, *fd, NULL) == -1) {
    _m(_msgfatal, "Failed to remove event from handler!");
    perror("epoll_ctl: ");
    return false;
  }

  _m(_msgdebug, "Removed [&%ld] listener!", *fd);
  return true;
}

void handle_close(const ssize_t* const fd) {
  _m(_msginfo, "Client <%ld> disconnected!", *fd);
  // Close the fd referring to the client just disconnected
  close(*fd);
}

void handle_disconnect(handler* const h, const ssize_t* const fd) {
  // In case handler cannot remove the listener exit with the status given by errno
  if (!handler_remove_listener(h, fd))
    exit(errno);
  handle_close(fd);
}
