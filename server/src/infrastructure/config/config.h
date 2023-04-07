/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/
#ifndef _CONFIG_PARSER_H
#define _CONFIG_PARSER_H
  #include <stdint.h>

  /***************************************************************************
  *                        CONFIGURATION STRUCTURE                           *
  ***************************************************************************/

  /* Structure used to hold configuration borrowed from the config file */
  typedef struct config {
    /* Configuration for network setting related */
    struct network_settings {
      char* host;
      char* port;
      char* timeout;
      //uint16_t port;
    } ns;

    /* Configuration for connection setting related */
    struct connection_settings {
      char* max_clients;
      char* max_threads;
    } cs;

    /* Configuration for logging setting related */
    struct logging_settings {
      char* log_level;
      char* log_file;
    } ls;

  } config;

  // Provide a default configuration in case something went wrong when loading the config file
  config* provide_default_config();



  /***************************************************************************
  *                     CONFIGURATION PARSING STRUCTURE                      *
  ***************************************************************************/

  /* Structure used to parse data  */
  typedef struct ini_parser {
    char* data;
    char* end;
  } ini_parser;

  /* Constructor for the parser with a given filename */
  ini_parser* init_parser(const char*);
  /* Destructor for the given parser */
  void destroy_parser(ini_parser*);
  /* Get a specific value from a given <parser, section, key> */
  const char* get_value(ini_parser*, const char*, const char*);

#endif
