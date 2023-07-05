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

  typedef struct request_t {
    char* request_type;		/* Type of the request: One of LOGIN, REGISTRATION, RETRIEVE, DELETE */
    char* credential_id;	/* Id of the caller */
    char* credential_username;	/* Username of the caller */
    char* credential_password;	/* Password of the caller */
  } request;

  typedef struct payload_t {
    void* data;
    size_t size;
  } payload_t;

  /**
   * Helper function used to parse a given data with 2 specified delimiters
   *
   * Example of usage:
   *
   * const char* input ="<>CALL,EXPECTED<>v3,v4,v5<>w1,w2<>x1,x2,x4<>y1,y2,y5,y6";
   * parse_data(input, "<>", ",");
  */
  request* parse_data(const char*, const char*, const char*);

  /** Destructor for the request */
  void destroy_request(request*);

#endif
