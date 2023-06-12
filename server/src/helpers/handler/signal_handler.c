/*
  ╔═╗  ╦  ╔═╗  ╔╗╔  ╔═╗  ╦        ╦ ╦  ╔═╗  ╔╗╔  ╔╦╗  ╦    ╔═╗  ╦═╗
  ╚═╗  ║  ║ ╦  ║║║  ╠═╣  ║        ╠═╣  ╠═╣  ║║║   ║║  ║    ║╣   ╠╦╝
  ╚═╝  ╩  ╚═╝  ╝╚╝  ╩ ╩  ╩═╝      ╩ ╩  ╩ ╩  ╝╚╝  ═╩╝  ╩═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include "../logging/logging.h"
#include "signal_handler.h"

#define _m(type, format, ...) _msgcategory(type, " SIGNAL HANDLER ", format __VA_OPT__(,) __VA_ARGS__)

volatile sig_atomic_t persist = 1;

void setup_signals(int sig, void (func)(int)) {
  struct sigaction sa = {
    .sa_flags = SA_RESTART,
    .sa_handler = func
  };
  sigemptyset(&sa.sa_mask);
  if (sigaction(sig, &sa, NULL) == -1) {
    _m(_msgfatal, "Failed to setup signal->action. Cause: %s", strerror(errno));
    perror("sigaction: ");
    exit(errno);
  }
}
