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

static inline struct tm get_time() {
  time_t t = time(NULL);
  return *localtime(&t);
}

void ftime_print(const char* format, ...) {
  // Variadic function
  va_list args;
  va_start(args, format);
  struct tm tm = get_time();
  printf(TIME_FORMAT, TIME_FORMAT_ARGS(tm));
  vprintf(format, args);
  va_end(args);
}

void log_format(const char* tag, const char* message, va_list args) {
  struct tm tm = get_time();
  printf(TIME_FORMAT "%s", TIME_FORMAT_ARGS(tm), tag);
  vprintf(message, args);
}

void log_error(const char* message, ...) {  va_list args;   va_start(args, message);    log_format("error", message, args);   va_end(args); }
void log_info(const char* message, ...)  {  va_list args;   va_start(args, message);    log_format("info", message, args);    va_end(args); }
void log_debug(const char* message, ...) {  va_list args;   va_start(args, message);    log_format("debug", message, args);   va_end(args); }
