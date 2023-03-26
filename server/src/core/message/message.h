/*
  ╔╦╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗
  ║║║  ║╣   ╚═╗  ╚═╗  ╠═╣  ║ ╦  ║╣ 
  ╩ ╩  ╚═╝  ╚═╝  ╚═╝  ╩ ╩  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _MESSAGE_H_
#define _MESSAGE_H_
  #include <stdio.h>
  #include <sys/socket.h>
  #include <string.h>

  #include "../../common/logging/logging.h"

  ssize_t msg_send(int, const void* const, size_t, int);
  ssize_t msg_recv(int, void*, ssize_t, int, bool* const);
#endif
