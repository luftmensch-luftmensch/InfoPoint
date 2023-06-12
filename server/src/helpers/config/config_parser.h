/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗      ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╔═╗  ╦═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦      ╠═╝  ╠═╣  ╠╦╝  ╚═╗  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝      ╩    ╩ ╩  ╩╚═  ╚═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _CONFIG_H_
#define _CONFIG_H_

  #include <stdio.h>
  #include <stdbool.h>

  #include "sys_queue.h"

  #ifndef CONFIG_SECTION_FLAT
    #define CONFIG_SECTION_FLAT	NULL	/* config is flat data (has no section) */
  #endif

  #ifndef COMMENT_CHARS
    #define COMMENT_CHARS ";"    /* default comment chars */
  #endif
  #ifndef KEYVAL_SEP
    #define KEYVAL_SEP '='    /* default key-val seperator character */
  #endif

  #ifndef STR_TRUE
    #define STR_TRUE "1"    /* default string valu of true */
  #endif
  #ifndef STR_FALSE
    #define STR_FALSE "0"    /* default string valu of false */
  #endif

  #ifndef CONFIG_INIT_MAGIC
    #define CONFIG_INIT_MAGIC    0x12F0ED1
  #endif

  typedef enum config_status {
    CONFIG_OK,                    /* ok (no error) */
    CONFIG_ERR_FILE,              /* file io error (file not exists, cannot open file, ...) */
    CONFIG_ERR_NO_SECTION,        /* section does not exist */
    CONFIG_ERR_NO_KEY,            /* key does not exist */
    CONFIG_ERR_MEMALLOC,          /* memory allocation failed */
    CONFIG_ERR_INVALID_PARAM,     /* invalid parametrs (as NULL) */
    CONFIG_ERR_INVALID_VALUE,     /* value of key is invalid (inconsistent data, empty data) */
    CONFIG_ERR_PARSING,           /* parsing error of data (does not fit to config format) */

  } config_status;


  typedef struct config_key_val {
    char* key;
    char* value;
    TAILQ_ENTRY(config_key_val) next;
  } config_key_val;

  typedef struct config_section {
    char *name;
    int numofkv;
    TAILQ_HEAD(, config_key_val) kv_list;
    TAILQ_ENTRY(config_section) next;
  } config_section;

  typedef struct config_parser {
    char *comment_chars;
    char keyval_sep;
    char *true_str;
    char *false_str;
    int  initnum;
    int  numofsect;
    TAILQ_HEAD(, config_section) sect_list;

  } config_parser;

  /* Initializator for the parser */
  config_parser* init_config();

  /* Destructor for the parser */
  void destroy_config(config_parser*);

  const char* config_status_to_str(config_status);

  /* Reads the specified file name and populate the parser */
  config_status read_config(FILE*, config_parser**);

  /* Open & reads the file in order to populate the entire content to the given parser */
  config_status read_file(const char*, config_parser**);

  /* Print to the specified stream the content of the parser */
  config_status print_config(const config_parser*, FILE*);

  /* Print to the specified stream the settings loaded */
  config_status print_config_settings(const config_parser*, FILE*);

  /* Returns the number of sections presents in the parser if the operation is successful, -1 otherwise */
  int get_config_section_count(const config_parser*);

  /* Returns the number of keys presents in the section if the operation is successful, -1 otherwise */
  int get_config_key_count(const config_parser*, const char*);

  /*
   * Set the type of the comment (`#`, `;`, etc...) to use to parse the ini file
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status set_config_comment_charset(config_parser*, const char*);

  /*
   * Set the <key,value> separator to use to parse the ini file
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status set_config_key_val_sep_charset(config_parser*, char ch);

  /*
   * Set the corresponding value to convert a boolean value to the corresponding C-Like value
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status set_config_bool_to_str(config_parser*, const char*, const char*);

  /*
   * Read a specific string from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_str_from_cfg(const config_parser*, const char*, const char*, char*, int, const char*);

  /*
   * Read a specific int from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_int_from_cfg(const config_parser*, const char*, const char*, int*,int);

  /*
   * Read a specific unsigned int from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_uint_from_cfg(const config_parser*, const char*, const char*, unsigned int*,unsigned int);

  /*
   * Read a specific float from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_float_from_cfg(const config_parser*, const char*, const char*, float*,float);

  /*
   * Read a specific double from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_double_from_cfg(const config_parser*, const char*, const char*, double*,double);

  /*
   * Read a specific boolean from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_boolean_from_cfg(const config_parser*, const char*, const char*, bool*, bool);


  /*
   * Add the specific <key,value (string)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_str_to_cfg(config_parser*, const char*, const char*, const char*);

  /*
   * Add the specific <key,value (int)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_int_to_cfg(config_parser*, const char*, const char*, int);

  /*
   * Add the specific <key,value (unsigned int)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_uint_to_cfg(config_parser*, const char*, const char*, unsigned int);

  /*
   * Add the specific <key,value (double)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_double_to_cfg(config_parser*, const char*, const char*, double);

  /*
   * Add the specific <key,value (boolean)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_boolean_to_cfg(config_parser*, const char*, const char*, bool);

  /* Check if a specified section exists in the parser */
  bool cfg_has_section(const config_parser*, const char*);
#endif
