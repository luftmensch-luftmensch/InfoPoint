/*
  ╦ ╦  ╔═╗  ╔═╗  ╦═╗
  ║ ║  ╚═╗  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _USER_H_
#define _USER_H_
  #include <stdlib.h>
  #include <netinet/in.h>

  #ifndef REGEX_NICKNAME

    /**
     * User nickname boundaries:
     * 1. Has to start with an alphanumeric;
     * 2. At least two characters;
     * 3. Has to end with an alphanumeric
    */
    #define REGEX_NICKNAME "^[a-zA-Z0-9]+[_@#]?[a-zA-Z0-9]+$"
  #endif

  typedef enum user_level {
    STANDARD,
    MEDIUM,
    EXPERT,
  } user_level;

  typedef struct user {
    char* name;
    char* password;
    user_level level;
  } user;

#endif
