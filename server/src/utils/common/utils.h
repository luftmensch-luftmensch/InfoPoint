#ifndef InfoPoint_Utils
#define InfoPoint_Utils


    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <time.h>
    #include <assert.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <errno.h>
    #include <signal.h>
    #include <regex.h>

    #ifndef IPV4_ADDRESS_FORMAT
	    #define IPV4_ADDRESS_FORMAT "%d.%d.%d.%d"
    #endif


    #define IPV4(IP) \
	    (IP & 0x000000ff) >> 0, \
	    (IP & 0x0000ff00) >> 8, \
	    (IP & 0x00ff0000) >> 16,\
	    (IP & 0xff000000) >> 24 \



    // Used for Login/Registration
    #ifndef REGEX_NICKNAME
	    // Has to start with an alphanumeric
	    // At least two characters 
	    // Has to end with an alphanumeric
	    #define REGEX_NICKNAME "^[a-zA-Z0-9]+[_@#]?[a-zA-Z0-9]+$"
    #endif

    // Buffer manipulation
    char* ltrim(char *s);
    char* rtrim(char *s);
    char* trim(char *s);
    bool validate_regex(const void * const, const void * const);

    // Random values
    void init_random();
    size_t random_in(const size_t, const size_t);

    // MSG Options
    void ftime_print(const char*, ...);

    #ifndef MSG_CATEGORY_SIZE
	    #define MSG_CATEGORY_SIZE 8
    #endif

    #ifndef MSG_FUNC_SIZE
	    #define MSG_FUNC_SIZE 24 
    #endif

    // Macros [Logging]
    #define _msgsystem(format, ...) ftime_print(format "\n", ##__VA_ARGS__)
    #define _msginfo(format, ...) _msgsystem(ANSI_COLOR_BLUE "(INFO):  " format ANSI_COLOR_RESET, ##__VA_ARGS__)
    #define _msgevent(format, ...) _msgsystem(ANSI_COLOR_BBLUE "(EVENT): " format ANSI_COLOR_RESET, ##__VA_ARGS__)
    #define _msgwarn(format, ...) _msgsystem(ANSI_COLOR_YELLOW "(WARN):  " format ANSI_COLOR_RESET, ##__VA_ARGS__)
    #define _msgfatal(format, ...) _msgsystem(ANSI_COLOR_BRED "(FATAL): " format ANSI_COLOR_RESET, ##__VA_ARGS__) 
    #define _msghighlight(format, ...)_msgsystem(ANSI_COLOR_CYAN "(LOOK):  " format ANSI_COLOR_RESET, ##__VA_ARGS__) 
    #define _msgcategory(type, category, format, ...) type("[%*s] " format, MSG_CATEGORY_SIZE, category, ##__VA_ARGS__)


    // These functions will output only if SHUTUP was not defined, in debug.
    #if defined(DEBUG) && !defined(SHUTUP)
	    #define _msgdebug(format, ...)		_msgsystem(ANSI_COLOR_GREEN "(DEBUG): " format ANSI_COLOR_RESET, ##__VA_ARGS__)
	    #define _msgsetting(format, ...)	_msgsystem(ANSI_COLOR_MAGENTA "(SETUP): " format ANSI_COLOR_RESET, ##__VA_ARGS__)
    #else
	    #define _msgdebug(format, ...)
	    #define _msgsetting(format, ...)
    #endif

    #ifndef InfoPoint_Color_Palette
    #define InfoPoint_Color_Palette

      #define ANSI_COLOR_RED "\x1b[31m"
      #define ANSI_COLOR_GREEN "\x1b[32m"
      #define ANSI_COLOR_YELLOW "\x1b[33m"
      #define ANSI_COLOR_BLUE "\x1b[34m"
      #define ANSI_COLOR_MAGENTA "\x1b[35m"
      #define ANSI_COLOR_CYAN "\x1b[36m"
      #define ANSI_COLOR_BRED "\x1b[91m"
      #define ANSI_COLOR_BGREEN "\x1b[92m"
      #define ANSI_COLOR_BYELLOW "\x1b[93m"
      #define ANSI_COLOR_BBLUE "\x1b[94m"
      #define ANSI_COLOR_BMAGENTA "\x1b[95m"
      #define ANSI_COLOR_BCYAN "\x1b[96m"
      #define ANSI_COLOR_RESET "\x1b[0m"

    #endif


    #ifndef TIME_FORMAT
      #define TIME_FORMAT "(%02d:%02d:%02d, %02d-%02d-%d)" 
      #define TIME_FORMAT_ARGS(tm) tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mday, tm.tm_mon + 1, 1900 + tm.tm_year // [Giorno - Mese - Anno] (ora:minuti:secondi)
    #endif

    void logging(char* message);
    void client_logging(char* message);
    void info_logging(int PORT, int MAX_CONNECTION);


#endif
