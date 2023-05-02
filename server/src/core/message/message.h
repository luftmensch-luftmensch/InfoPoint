/*
  ╔╦╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗
  ║║║  ║╣   ╚═╗  ╚═╗  ╠═╣  ║ ╦  ║╣ 
  ╩ ╩  ╚═╝  ╚═╝  ╚═╝  ╩ ╩  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _MESSAGE_H_
#define _MESSAGE_H_
  #include <stdio.h>
  #include <sys/socket.h>
  #include <string.h>

  #include "../../infrastructure/logging/logging.h"

  ssize_t msg_send(int, const void* const, size_t, int);
  ssize_t msg_recv(int, void*, ssize_t, int, bool* const);
#endif
