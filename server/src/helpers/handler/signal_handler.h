/*
  ╔═╗  ╦  ╔═╗  ╔╗╔  ╔═╗  ╦        ╦ ╦  ╔═╗  ╔╗╔  ╔╦╗  ╦    ╔═╗  ╦═╗
  ╚═╗  ║  ║ ╦  ║║║  ╠═╣  ║        ╠═╣  ╠═╣  ║║║   ║║  ║    ║╣   ╠╦╝
  ╚═╝  ╩  ╚═╝  ╝╚╝  ╩ ╩  ╩═╝      ╩ ╩  ╩ ╩  ╝╚╝  ═╩╝  ╩═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _SIGNAL_HANDLER_H_
#define _SIGNAL_HANDLER_H_

  #include <signal.h>

  /** Helper function used to setup a signal handler to stop the execution gracefully */
  void setup_signals(int, void (func)(int));
#endif
