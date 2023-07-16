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
  #include "../base/macros.h"


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

  /** Initializator for the parser */
  config_parser* init_config();

  /** Destructor for the parser */
  void destroy_config(config_parser*);

  /** Reads the specified file name and populate the parser */
  config_status read_config(FILE*, config_parser**);

  /** Open & reads the file in order to populate the entire content to the given parser */
  config_status read_file(const char*, config_parser**);

  /**
   * Read a specific string from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_str_from_cfg(const config_parser*, const char*, const char*, char*, int, const char*);

  /**
   * Read a specific unsigned int from a given parser matching a specified key.
   * If any error occurs default value is copied to 'value' buffer and a given error is returned
   * If the key is optional and does not exists in the config the value is copied and the return status is CONFIG_ERR_NO_KEY
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status  read_uint_from_cfg(const config_parser*, const char*, const char*, unsigned int*,unsigned int);


  /**
   * Add the specific <key,value (string)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_str_to_cfg(config_parser*, const char*, const char*, const char*);

  /**
   * Add the specific <key,value (unsigned int)> pair to the specified parser
   * It returns CONFIG_RET_OK if the operation is successful, otherwise an error is returned
  */
  config_status add_uint_to_cfg(config_parser*, const char*, const char*, unsigned int);

#endif
