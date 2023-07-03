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
    size_t size;
  } payload_t;

  /**
   * Helper function used to parse a given data with 2 specified delimiters
   *
   * Example of usage:
   *
   * const char* input ="CALL,EXPECTED,v3,v4,v5<>w1,w2,<>x1,x2,x4<>y1,y2,y5,y6";
   * parse_data(input, "<>", ",");
  */
  void parse_data(const char*, const char*, const char*);


#endif
