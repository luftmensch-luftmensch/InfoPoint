/*
  ╦ ╦┌─┐┌┐┌┌┬┐┬  ┌─┐┬─┐┌┬┐┌─┐
  ╠═╣├─┤│││ │││  ├┤ ├┬┘ ││└─┐
  ╩ ╩┴ ┴┘└┘─┴┘┴─┘└─┘┴└──┴┘└─┘
  Autori:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
  
*/

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include "handlers.h"

#define _m(type, format, ...) _msgcategory(type, "UTILITY", format, ##__VA_ARGS__)
volatile sig_atomic_t persist = 1;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock_condition = PTHREAD_MUTEX_INITIALIZER;

static inline struct tm get_time() {
  time_t t = time(NULL);
  return *localtime(&t);
}

void handle_interrupt(int sig){
	(void)sig;
	pthread_cond_signal(&cond1); 
	persist = 0; 
}

void setup_signals(){
  struct sigaction sa;

  sa.sa_handler = handle_interrupt;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  if(sigaction(SIGINT, &sa, NULL) == -1){
    _msgfatal("[SIG] Error on signal setup!");
    perror("sigaction: "); exit(errno);
  }
}

char *ltrim(char *s) {
	while(isspace(*s)) s++;
	return s;
}

char *rtrim(char *s){
	char* back = s + strlen(s);
	while(isspace(*--back));
	*(back+1) = '\0';
	return s;
}

char *trim(char *s){
	return rtrim(ltrim(s)); 
}

// Initialize random generator
void init_random(){
	srand(time(NULL));
}

// Returns a random number within th range 
size_t random_in(size_t min, size_t max){
	return (rand() % (max - min + 1)) + min;
}

// Case-Insensitive Regex, returns true if string was matched against pattern
bool validate_regex(const void * const s, const void * const pattern){
	if(!s){
		_m(_msgwarn, "[REGEX] No value given for pattern!", (char*)pattern);
		return true;
	}

	_m(_msgdebug, "[REGEX] Checking [s: <%s>] matches [rgx: <%s>]", (char*)s, (char*)pattern);
	regex_t rgx;
	int comparison_value = regcomp(&rgx, (char*)pattern, REG_EXTENDED | REG_NOSUB);

	// If regcomp failed to initialize th regex pattern
	if(comparison_value){
		_m(_msgwarn, "[REGEX] <%s> is not a valid regex!", (char*)pattern);
		return true;
	}
	
	// As regexec returns 0 if pattern was found, we capture the opposite
	comparison_value = !regexec(&rgx, (char*)s, 0, NULL, 0);
	regfree(&rgx);
	_m(_msgdebug, "[REGEX] string <%s> %s!", (char*)s, comparison_value ? "accepted":"refused");
	return comparison_value;
}

// Print time and msg
// Debug only!
void ftime_print(const char *format, ...){
	// Format string with parameters
	va_list args; 
	va_start(args, format); 
	struct tm tm = get_time();
	printf("[TIME] " TIME_FORMAT, TIME_FORMAT_ARGS(tm));
	vprintf(format, args);
	va_end(args);
}


// Funzione per il logging con l'orario
void logging(char* message){
  struct tm time = get_time();
  printf(ANSI_COLOR_GREEN "%s " ANSI_COLOR_RESET ANSI_COLOR_BLUE TIME_FORMAT ANSI_COLOR_RESET "\n", message, TIME_FORMAT_ARGS(time));
}

void client_logging(char* message){
  struct tm time = get_time();
  printf(ANSI_COLOR_CYAN "[+]Connesso con il client con IP:["
	 ANSI_COLOR_BGREEN "%s"
	 ANSI_COLOR_CYAN "]"
	 ANSI_COLOR_RESET
	 ANSI_COLOR_BLUE
	 TIME_FORMAT ANSI_COLOR_RESET "\n", message, TIME_FORMAT_ARGS(time));
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
