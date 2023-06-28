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

    #include "../logging/logging.h"

    // Buffer manipulation
    char* ltrim(char *s);
    char* rtrim(char *s);
    char* trim(char *s);

    bool validate_regex(const void * const, const void * const);

    /* Count the occurence of a given delimeter inside a given buffer */
    size_t count_occurence(const char*, const char*);
    // int count_occurence(const char*, const char*, bool);

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
