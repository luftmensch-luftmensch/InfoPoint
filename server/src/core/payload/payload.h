/*
  ╔═╗  ╔═╗  ╦ ╦  ╦    ╔═╗  ╔═╗  ╔╦╗
  ╠═╝  ╠═╣  ╚╦╝  ║    ║ ║  ╠═╣   ║║
  ╩    ╩ ╩   ╩   ╩═╝  ╚═╝  ╩ ╩  ═╩╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _PAYLOAD_H_
#define _PAYLOAD_H_

  #include <stdlib.h>
  #include <stdbool.h>

  typedef struct payload_t {
    void* data;
    size_t length;
  } payload_t;

#endif
