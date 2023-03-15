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
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include "utils.h"

#define _m(type, format, ...) _msgcategory(type, "UTILITY", format, ##__VA_ARGS__)

static inline struct tm get_time() {
  time_t t = time(NULL);
  return *localtime(&t);
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

int count_occurence(const char *str, const char* substr, bool overlap) {
  if ((strlen(substr) == 0) || (strlen(str) == 0)) return -1; // forbid empty substr

  int count = 0;
  int increment = overlap ? 1 : strlen(substr);
  for (char* s = (char*)str; (s = strstr(s, substr)); s += increment)
    ++count;
  return count;
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
	// TODO: Move to write
	printf(TIME_FORMAT, TIME_FORMAT_ARGS(tm));
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
