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
      char* host;    // The host on which the server should run
      char* port;    // The port that the server should use
      char* timeout; // Timeout after which a connection should stop
    } ns;

    /* Configuration for connection setting related */
    struct connection_settings {
      char* max_clients; // N° of clients that the server should accept
      char* max_threads; // N° of threads that the server should use
    } cs;

    /* Configuration for database setting related */
    struct database_settings {
      char* type; // Type of the specified database
      char* host; // Host of the running database
      char* port; // Port of the running database
    } ds;

    /* Configuration for logging setting related */
    struct logging_settings {
      char* log_level; // Logging level
      char* log_file;  // File on which make logging operations
    } ls;

  } config;

  // Provide a default configuration in case something went wrong when loading the config file
  //config* provide_default_config();

  // Provide a config filled out with the given config file or a default one in case something went wrong when loading/parsing the config file
  config* provide_config(const char*);



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
