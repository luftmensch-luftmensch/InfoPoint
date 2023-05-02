/*
  ╦    ╔═╗  ╔═╗  ╔═╗  ╦  ╔╗╔  ╔═╗
  ║    ║ ║  ║ ╦  ║ ╦  ║  ║║║  ║ ╦
  ╩═╝  ╚═╝  ╚═╝  ╚═╝  ╩  ╝╚╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include "logging.h"
#include <stdarg.h>
#include <stdio.h>

void ftime_print(const char* format, ...){
  // Variadic function
  va_list args;
  va_start(args, format);
  struct tm tm = get_time();
  printf(TIME_FORMAT, TIME_FORMAT_ARGS(tm));
  vprintf(format, args);
  va_end(args);
}
