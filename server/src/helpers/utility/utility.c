/*
  ╦ ╦  ╔╦╗  ╦  ╦    ╦  ╔╦╗  ╦ ╦
  ║ ║   ║   ║  ║    ║   ║   ╚╦╝
  ╚═╝   ╩   ╩  ╩═╝  ╩   ╩    ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <regex.h>
#include <sys/time.h>
#include <time.h>

#include "utility.h"

#define _m(type, format, ...) _msgcategory(type, " UTILITY ", format __VA_OPT__(,) __VA_ARGS__)

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
bool validate_regex(const void * const s, const void * const pattern) {
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

static off_t get_file_size (const char * file_name) { // off_t -> same as unsigned long long int
  struct stat sb;
  if (stat (file_name, & sb) != 0) {
    fprintf (stderr, "[%s] (%s) 'stat' failed for '%s': %s.\n", __FILE_NAME__, __func__, file_name, strerror (errno));
    exit (EXIT_FAILURE);
  }
  return sb.st_size;
}

unsigned char* file_reader(const char* file_name) {
  if (file_name == NULL) {
    fprintf(stderr, "[%s] (%s) Invalid file_name!", __FILE__, __func__);
    return NULL;
  }

  off_t bytes_read;
  FILE* fp;
  unsigned char* buffer;

  // Get the size of the specified file
  off_t size = get_file_size(file_name);

  if (!(buffer = malloc(size + 1))) { // Check if we can allocate enought space to put the content of the file in the buffer
    fprintf(stderr, "[%s] (%s) Failed to allocate enought space to store the specified file name <%s>", __FILE__, __func__, file_name);
    exit (EXIT_FAILURE);
  }

  if (!(fp = fopen(file_name, "r"))) { // Try to open the file in read mode
    fprintf(stderr, "[%s] (%s) Failed to open the given file name <%s> -> %s", __FILE__, __func__, file_name, strerror(errno));
    return NULL;
  }

  // Try to read the given file
  bytes_read = fread(buffer, sizeof(unsigned char), size, fp);

  // Check if the bytes read matches the size of the specified file
  if (bytes_read != size) {
    fprintf(stderr, "[%s] (%s) Short read of <%s>: Expected %ld bytes, but got %zu: %s", __FILE__, __func__, file_name, size, bytes_read, strerror(errno));
    return NULL;
  }

  // Handle file descriptor close
  if (fclose(fp) != 0){
    fprintf(stderr, "[%s] (%s) Failed to close <%s>: %s", __FILE_NAME__, __func__, file_name, strerror(errno));
    return NULL;
  }

  // The fread function simply reads a number of elements, it has no notion of "strings".
  // fread doesn't handle this for you. It must be done manually
  buffer[size] = '\0';

  return buffer;
}

char* concatenate(int count, ...) {
  va_list ap;

  // Find required length to store merged string
  int len = 1; // room for NULL
  va_start(ap, count);
  for(int i=0; i< count; i++)
    len += strlen(va_arg(ap, char*));
  va_end(ap);

  // Allocate memory to concat strings
  char* merged = calloc(sizeof(char), len);
  int null_pos = 0;

  // Actually concatenate strings
  va_start(ap, count);

  for(int i=0; i<count; i++) {
    char *s = va_arg(ap, char*);
    strcpy(merged+null_pos, s);
    null_pos += strlen(s);
  }

  va_end(ap);

  return merged;
}
