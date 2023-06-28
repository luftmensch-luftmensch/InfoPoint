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

  typedef enum request_t {
    LOGIN,
    REGISTRATION,
    ARTWORKS
  } request_t;

  typedef struct payload_t {
    request_t request;
    void* data;
    size_t length;
  } payload_t;

  /* TODO: Change current return type */
  void parse_data(const char*, const char*, const char*);

#endif
