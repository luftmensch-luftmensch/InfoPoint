/*
  ╦ ╦  ╔╦╗  ╦  ╦    ╦  ╔╦╗  ╦ ╦
  ║ ║   ║   ║  ║    ║   ║   ╚╦╝
  ╚═╝   ╩   ╩  ╩═╝  ╩   ╩    ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _UTILITY_H_
#define _UTILITY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <unistd.h>
    #include <errno.h>
    #include <assert.h>
    #include <ctype.h>
    #include <sys/time.h>

    #include <time.h>
    #include <signal.h>
    #include <pthread.h>

    #include <regex.h>
    #include "../logging/logging.h"

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

    /* Count the occurence of a given delimeter inside a given buffer */
    int count_occurence(const char*, const char*, bool);

    /* Strip a given delimeter from a given buffer */
    /* TODO: Change return type */
    void strip_data(char*, const char*);

    /* Return the current timestamp in milliseconds */
    long long current_timestamp();

#endif
