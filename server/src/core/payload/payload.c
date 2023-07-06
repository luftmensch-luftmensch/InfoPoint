/*
  ╔═╗  ╔═╗  ╦ ╦  ╦    ╔═╗  ╔═╗  ╔╦╗
  ╠═╝  ╠═╣  ╚╦╝  ║    ║ ║  ╠═╣   ║║
  ╩    ╩ ╩   ╩   ╩═╝  ╚═╝  ╩ ╩  ═╩╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "payload.h"

#include "../../helpers/logging/logging.h"
#include "../../helpers/utility/utility.h"


#define _m(type, format, ...) _msgcategory(type, " PAYLOAD ", format __VA_OPT__(,) __VA_ARGS__)

request* parse_data(const char* input, const char* outer_block, const char* inner_block) {
  char* copy = strdup(input);

  char *set_track, *elem_track;

  char* set;
  char* _input = copy;

  size_t counter = 0;

  if (count_occurence(_input, outer_block) != count_occurence(_input, inner_block))
    return NULL;

  request* r = malloc(sizeof(struct request_t));

  while((set = strtok_r(_input, outer_block, &set_track))) {
    _input = NULL; // For subsequent calls of strtok_r
    char* value;

    // In this case I don't care about strtok messing with the input
    char *_set_input = set; // same trick as above
    while((value = strtok_r(_set_input, inner_block, &elem_track))) {
      _set_input = NULL; // for subsequent calls of strtok_r
      switch (counter) {
      case 1:			/* Retrieve request */
	r->request_type = malloc(sizeof(char) * (strlen(value) + 1));
	memcpy(r->request_type, value, (strlen(value) + 1));
	break;
      case 3:			/* Retrieve username */
	r->credential_username = malloc(sizeof(char) * (strlen(value) + 1));
	memcpy(r->credential_username, value, (strlen(value) + 1));
	break;
      case 5:			/* Retrieve password */
	r->credential_password = malloc(sizeof(char) * (strlen(value) + 1));
	memcpy(r->credential_password, value, (strlen(value) + 1));
	break;
      case 7:			/* Retrieve TOKEN */
	r->token = malloc(sizeof(char) * (strlen(value) + 1));
	memcpy(r->token, value, (strlen(value) + 1));
	break;
      case 2:
      case 4:
      case 6:
	/* Nothing to do here -> Those are the keys */
	break;
      default:
	break;
      }

      counter++;
    }
  }

  free(copy);
  return r;
}

void destroy_request(request* r) {
  if (r == NULL)
    return;

  if (r->request_type) free(r->request_type);
  if (r->credential_username) free(r->credential_username);
  if (r->credential_password) free(r->credential_password);
  if (r->token) free(r->token);

  free(r);
}
