/*
  ╦ ╦  ╔╦╗  ╦  ╦    ╦  ╔╦╗  ╦ ╦
  ║ ║   ║   ║  ║    ║   ║   ╚╦╝
  ╚═╝   ╩   ╩  ╩═╝  ╩   ╩    ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
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

    #define typename(x) _Generic((x),        /* Get the name of a type */             \
										      \
	    _Bool: "_Bool",                  unsigned char: "unsigned char",          \
	     char: "char",                     signed char: "signed char",            \
	short int: "short int",         unsigned short int: "unsigned short int",     \
	      int: "int",                     unsigned int: "unsigned int",           \
	 long int: "long int",           unsigned long int: "unsigned long int",      \
    long long int: "long long int", unsigned long long int: "unsigned long long int", \
	    float: "float",                         double: "double",                 \
      long double: "long double",                   char *: "pointer to char",        \
	   void *: "pointer to void",                int *: "pointer to int",         \
	  default: "other")


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


    /*
     * Reads an entire file into a dynamically allocated memory buffer.
     * The returned buffer needs to be free()d afterwards
    */
    unsigned char* file_reader(const char*);
    /*
      Variadic function to concatenate any number of strings


      Example usage:
      ```
	int main(int argc, char* argv[]) {
	char *str;

	str = concat(0);             printf("%s", str); free(str);
	str = concat(1,"a");         printf("%s", str); free(str);
	str = concat(2,"a","b");     printf("%s", str); free(str);

	return 0;
	}
      ```
    */
    char* concatenate(int, ...);

#endif
