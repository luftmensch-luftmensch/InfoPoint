/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗      ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╔═╗  ╦═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦      ╠═╝  ╠═╣  ╠╦╝  ╚═╗  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝      ╩    ╩ ╩  ╩╚═  ╚═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/


#ifndef _CONFIG_PARSER_H
#define _CONFIG_PARSER_H

  #include <stdio.h>
  #include <stdlib.h>
  #include <stdint.h>
  #include <stdbool.h>

  #define JSON_MAJOR 	1
  #define JSON_MINOR	0
  #define JSON_VERSION	(JSON_MAJOR * 100 + JSON_MINOR)

  #define PARSER_DEFAULT_STACK_SIZE 256
  #define PARSER_DEFAULT_BUFFER_SIZE 4096

  #define CHK(f) do { ret = f; if (ret) return ret; } while(0)

  typedef enum json_type {
    JSON_NONE,
    JSON_ARRAY_BEGIN,
    JSON_OBJECT_BEGIN,
    JSON_ARRAY_END,
    JSON_OBJECT_END,
    JSON_INT,
    JSON_FLOAT,
    JSON_STRING,
    JSON_KEY,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL,
    JSON_BSTRING,
  } json_type;

  typedef enum json_error {
    /* SUCCESS = 0 */
    /* running out of memory */
    JSON_ERROR_NO_MEMORY = 1,
    /* character < 32, except space newline tab */
    JSON_ERROR_BAD_CHAR,
    /* trying to pop more object/array than pushed on the stack */
    JSON_ERROR_POP_EMPTY,
    /* trying to pop wrong type of mode. popping array in object mode, vice versa */
    JSON_ERROR_POP_UNEXPECTED_MODE,
    /* reach nesting limit on stack */
    JSON_ERROR_NESTING_LIMIT,
    /* reach data limit on buffer */
    JSON_ERROR_DATA_LIMIT,
    /* comment are not allowed with current configuration */
    JSON_ERROR_COMMENT_NOT_ALLOWED,
    /* unexpected char in the current parser context */
    JSON_ERROR_UNEXPECTED_CHAR,
    /* unicode low surrogate missing after high surrogate */
    JSON_ERROR_UNICODE_MISSING_LOW_SURROGATE,
    /* unicode low surrogate missing without previous high surrogate */
    JSON_ERROR_UNICODE_UNEXPECTED_LOW_SURROGATE,
    /* found a comma not in structure (array/object) */
    JSON_ERROR_COMMA_OUT_OF_STRUCTURE,
    /* callback returns error */
    JSON_ERROR_CALLBACK,
    /* utf8 stream is invalid */
    JSON_ERROR_UTF8,
  } json_error;

  /* Callback fun for the parser */
  typedef int (*parser_callback)(void*, int, const char*, uint32_t);

  /* Callback fun for the printer */
  typedef int (*printer_callback)(void*, const char*, uint32_t);

  typedef struct json_config {
    uint32_t buffer_initial_size;
    uint32_t max_nesting;
    uint32_t max_data;
    int allow_c_comments;
    int allow_yaml_comments;

    void* (*u_calloc)(size_t nmemb, size_t size);
    void* (*u_realloc)(void *ptr, size_t size);

  } json_config;

  typedef struct parser {
	  json_config config;

	  /* SAJ callback */
	  parser_callback callback;
	  void* userdata;

	  /* parser state */
	  uint8_t   state;
	  uint8_t   save_state;
	  uint8_t   expecting_key;
	  uint8_t   utf8_multibyte_left;
	  uint16_t  unicode_multi;
	  json_type type;

	  /* state stack */
	  uint8_t* stack;
	  uint32_t stack_offset;
	  uint32_t stack_size;

	  /* parse buffer */
	  char*    buffer;
	  uint32_t buffer_size;
	  uint32_t buffer_offset;
  } parser;

  typedef struct printer {
	  printer_callback callback;
	  void* userdata;

	  char* indentstr;
	  int indentlevel;
	  int afterkey;
	  int enter_object;
	  int first;
  } printer;

  typedef struct json_val_elem {
    char* key;
    uint32_t key_length;
    struct json_val* val;
  } json_val_elem;

  typedef struct json_val {
    int type;
    int length;
    union {
      char* data;
      struct json_val** array;
      struct json_val_elem** object;
    } u;
  } json_val_t;

  /** callback from the parser_dom callback to create object and array */
  typedef void * (*dom_create_structure)(int, int);

  /** callback from the parser_dom callback to create data values */
  typedef void * (*dom_create_data)(int, const char *, uint32_t);

  /** callback from the parser helper callback to append a value to an object or array value
   * append(parent, key, key_length, val); */
  typedef int (*dom_append)(void *, char *, uint32_t, void *);

  /*
   * Permits to create a DOM like tree easily through the
   * use of 3 callbacks where the user can choose the representation of the JSON values
  */
  typedef struct dom {
	  /* object stack */
	  struct stack_elem { void *val; char *key; uint32_t key_length; } *stack;
	  uint32_t stack_size;
	  uint32_t stack_offset;

	  /* overridable memory allocator */
	  void * (*user_calloc)(size_t nmemb, size_t size);
	  void * (*user_realloc)(void *ptr, size_t size);

	  /* returned root structure (object or array) */
	  void *root_structure;

	  /* callbacks */
	  dom_create_structure create_structure;
	  dom_create_data create_data;
	  dom_append append;
  } dom;

  // Function prototypes for parser

  /*
   * Initialize a parser taking a config and its data.
   * Return JSON_ERROR_NO_MEMORY if memory allocation failed or SUCCESS.
  */
  int init_parser(parser*, json_config*, parser_callback, void*);

  /* Destructor of parser */
  int destroy_parser(parser*);

  /*
   * Append a string s with a specific length to the parser
   * return 0 if everything went ok, a JSON_ERROR_* otherwise.
   * the user can supplied a valid processed pointer that will
   * be fill with the number of processed characters before returning
  */
  int parse_string(parser*, const char*, uint32_t, uint32_t*);

  /*
   * Append one single char to the parser
   * return 0 if everything went ok, a JSON_ERROR_* otherwise
  */
  //int parse_char(parser*, unsigned char);

  /* Return false is the parser isn't in a finish state otherwise true */
  int parser_is_done(parser*);

  // Function prototypes for printer

  /* Initialize a printer context. always succeed */
  int init_printer(printer*, printer_callback, void*);

  /*
   * Free a printer context
   * doesn't do anything now, but in future print_init could allocate memory
  */
  //int destroy_printer(printer*);

  /* Pretty print the passed argument (type/data/length). */
  //int printer_pretty(printer*, int, const char*, uint32_t);

  /* Prints without eye candy the passed argument (type/data/length). */
  //int printer_raw(printer*, int, const char*, uint32_t);


  // Function prototypes for dom

  /* initialize a parser dom structure with the necessary callbacks */
  int init_dom(dom*, dom_create_structure, dom_create_data, dom_append);

  /* Destructor for dom */
  int destroy_dom(dom*);

  /* helper to parser callback that arrange parsing events into comprehensive JSON data structure */
  int dom_callback(void*, int, const char*, uint32_t);

  /* File related func */

  /* Open requested filename */
  FILE *open_filename(const char*, const char*, int);

  /* Close requested filename */
  void close_filename(const char*, FILE*);

  /* Process file (Reading & Parsing) */
  int process_file(parser*, FILE*, int*, int*);

#endif
