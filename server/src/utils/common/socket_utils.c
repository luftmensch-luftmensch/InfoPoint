/*
  ╦ ╦  ┌┬┐  ┬  ┬    ┌─┐
  ║ ║   │   │  │    └─┐
  ╚═╝   ┴   ┴  ┴─┘  └─┘
  Autori:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h> // Necessario per la macro EXIT_FAILURE
#include "socket_utils.h"

int check(int expr, const char* msg){
  if(expr == SOCKET_ERROR){
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return expr;
}
