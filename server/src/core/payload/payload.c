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


#define _m(type, format, ...) _msgcategory(type, " PAYLOAD ", format __VA_OPT__(,) __VA_ARGS__)

void parse_data(const char* input, const char* delim_block, const char* delim_single) {
  char* copy = strdup(input);

  char *set_track, *elem_track;

  char* set;
  char* _input = copy;

  size_t set_num = 0;

  while((set = strtok_r(_input, delim_block, &set_track))) {
    _input = NULL; // For subsequent calls of strtok_r
    _m(_msginfo, "[%s] (%s) Set %zu contains: ", __FILE_NAME__, __func__, ++set_num);

    char* value;
    // in this case I don't care about strtok messing with the input
    char *_set_input = set; // same trick as above
    while((value = strtok_r(_set_input, delim_single, &elem_track))) {
      _set_input = NULL; // for subsequent calls of strtok_r
      _m(_msginfo, "[%s] (%s) Value: %s", __FILE_NAME__, __func__, value);
    }
  }

  free(copy);
}
