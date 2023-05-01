/*
  ╦ ╦  ╔╦╗  ╦  ╦    ╦  ╔╦╗  ╦ ╦
  ║ ║   ║   ║  ║    ║   ║   ╚╦╝
  ╚═╝   ╩   ╩  ╩═╝  ╩   ╩    ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "utility.h"


#define _m(type, format, ...) _msgcategory(type, "UTILITY", format, ##__VA_ARGS__)

// Buffer manipulation
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

char *trim(char *s){ return rtrim(ltrim(s)); }

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

int count_occurence(const char *str, const char* substr, bool overlap) {
  if ((strlen(substr) == 0) || (strlen(str) == 0)) return -1; // forbid empty substr

  int count = 0;
  size_t increment = overlap ? 1 : strlen(substr);
  for (char* s = (char*)str; (s = strstr(s, substr)); s += increment)
    ++count;
  return count;
}

long long current_timestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/* static off_t get_file_size (const char* file_name) { // off_t -> same as unsigned long long int */
/*   struct stat sb; */
/*   if (stat (file_name, & sb) != 0) { */
/*     fprintf (stderr, "'stat' failed for '%s': %s.\n", file_name, strerror (errno)); */
/*     exit (EXIT_FAILURE); */
/*   } */
/*   return sb.st_size; */
/* } */


/*
unsigned char* file_reader(const char* file_name) {
  if (file_name == NULL) {
    fprintf(stderr, "[%s] (%s) Failed to read the given file name (It's value is NULL!)", __FILE__, __func__);
    return NULL;
  }

  off_t size = get_file_size(file_name);
  unsigned char* content;
  FILE* fp;
  size_t bytes_read;

  if (!(content = malloc(size + 1))) {
    fprintf(stderr, "[%s] (%s) Failed to allocate enought space to store the specified file name <%s>", __FILE__, __func__, file_name);
    return NULL;
  }


  if(!(fp = fopen(file_name, "r"))) { // Try to open the file in read mode
    fprintf(stderr, "[%s] (%s) Failed to open the given file name <%s> -> %s", __FILE__, __func__, file_name, strerror(errno));
    return NULL;
  }

  // Try to read the given file
  bytes_read = fread(content, sizeof(unsigned char), size, fp);

  if (bytes_read != size) {
    fprintf (stderr, "Short read of '%s': expected %d bytes " "but got %zu: %s.\n", file_name, size, bytes_read, strerror (errno));
    return NULL;
  }

  if (fclose(fp) != 0){
    fprintf (stderr, "Error closing '%s': %s.\n", file_name, strerror (errno));
    return NULL;
  }
  return content;
}
*/
