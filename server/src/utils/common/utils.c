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
#include "utils.h"


// Ritorna la data e tempo corrente
static inline struct tm get_time() {
  time_t t = time(NULL);
  return *localtime(&t);
}

// Funzione per il logging con l'orario
void logging(char* message){
  struct tm time = get_time();
  printf(ANSI_COLOR_GREEN "%s " ANSI_COLOR_RESET ANSI_COLOR_BLUE TIME_FORMAT ANSI_COLOR_RESET "\n", message, TIME_FORMAT_ARGS(time));
}

void info_logging(int PORT, int MAX_CONNECTION) {
  struct tm time = get_time();
  printf(ANSI_COLOR_GREEN "[+] Server in ascolto sulla porta"
	 ANSI_COLOR_CYAN " %d "
	 ANSI_COLOR_GREEN "con un numero massimo di "
	 ANSI_COLOR_CYAN " %d "
	 ANSI_COLOR_GREEN "connessioni"
	 TIME_FORMAT ANSI_COLOR_RESET "\n", PORT, MAX_CONNECTION, TIME_FORMAT_ARGS(time));
}


int check(int expr, const char* msg){
  if(expr == SOCKET_ERROR){
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return expr;
}
