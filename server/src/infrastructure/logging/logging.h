/*
  ╦    ╔═╗  ╔═╗  ╔═╗  ╦  ╔╗╔  ╔═╗
  ║    ║ ║  ║ ╦  ║ ╦  ║  ║║║  ║ ╦
  ╩═╝  ╚═╝  ╚═╝  ╚═╝  ╩  ╝╚╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef LOGGING_H_
#define LOGGING_H_
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <time.h>
  #include <assert.h>
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <errno.h>
  #include <signal.h>

  #ifndef TIME_FORMAT
      #define TIME_FORMAT "%02d:%02d:%02d "
  #endif

  #ifndef DATETIME_FORMAT
      #define DATETIME_FORMAT "%2d/%02d at " TIME_FORMAT
  #endif


  #ifndef __FILE_NAME__
    #define __FILE_NAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
  #endif


  #define TIME_FORMAT_ARGS(tm) tm.tm_hour, tm.tm_min, tm.tm_sec
  #define DATETIME_FORMAT_ARGS(tm) tm.mday, tm.mon + 1, TIME_FORMAT_ARGS(tm)

  #ifndef IPV4_ADDRESS_FORMAT
      #define IPV4_ADDRESS_FORMAT "%d.%d.%d.%d"
  #endif

  static inline struct tm get_time(){
    time_t t = time(NULL);
    return *localtime(&t);
  }

  // Color definition
  #define ANSI_COLOR_RED      "\x1b[31m"
  #define ANSI_COLOR_GREEN    "\x1b[32m"
  #define ANSI_COLOR_YELLOW   "\x1b[33m"
  #define ANSI_COLOR_BLUE     "\x1b[34m"
  #define ANSI_COLOR_MAGENTA  "\x1b[35m"
  #define ANSI_COLOR_CYAN     "\x1b[36m"
  #define ANSI_COLOR_BRED     "\x1b[91m"
  #define ANSI_COLOR_BGREEN   "\x1b[92m"
  #define ANSI_COLOR_ORANGE   "\x1b[93m"
  #define ANSI_COLOR_BBLUE    "\x1b[94m"
  #define ANSI_COLOR_BMAGENTA "\x1b[95m"
  #define ANSI_COLOR_BCYAN    "\x1b[96m"
  #define ANSI_COLOR_RESET    "\x1b[0m"

  #ifndef MSG_CATEGORY_SIZE
      #define MSG_CATEGORY_SIZE 8
  #endif

  #ifndef MSG_FUNC_SIZE
      #define MSG_FUNC_SIZE 24 
  #endif

  void ftime_print(const char*, ...);
  #define _msgsystem(format, ...)    ftime_print(format "\n", ##__VA_ARGS__)
  #define _msginfo(format, ...)      _msgsystem(ANSI_COLOR_BLUE "(INFO):  " format ANSI_COLOR_RESET, ##__VA_ARGS__)
  #define _msgevent(format, ...)     _msgsystem(ANSI_COLOR_BBLUE "(EVENT): " format ANSI_COLOR_RESET, ##__VA_ARGS__)
  #define _msgwarn(format, ...)      _msgsystem(ANSI_COLOR_YELLOW "(WARN):  " format ANSI_COLOR_RESET, ##__VA_ARGS__)
  #define _msgfatal(format, ...)     _msgsystem(ANSI_COLOR_BRED "(FATAL): " format ANSI_COLOR_RESET, ##__VA_ARGS__) 
  #define _msghighlight(format, ...) _msgsystem(ANSI_COLOR_CYAN "(LOOK):  " format ANSI_COLOR_RESET, ##__VA_ARGS__) 
  #define _msgcategory(type, category, format, ...) type("[%*s] " format, MSG_CATEGORY_SIZE, category, ##__VA_ARGS__)

  // These functions will output only if SHUTUP was not defined, in debug.
  #if defined(DEBUG) && !defined(SHUTUP)
      #define _msgdebug(format, ...)   _msgsystem(ANSI_COLOR_GREEN "(DEBUG): " format ANSI_COLOR_RESET, ##__VA_ARGS__)
      #define _msgsetting(format, ...) _msgsystem(ANSI_COLOR_MAGENTA "(SETUP): " format ANSI_COLOR_RESET, ##__VA_ARGS__)
  #else
      #define _msgdebug(format, ...)
      #define _msgsetting(format, ...)
  #endif

#endif
