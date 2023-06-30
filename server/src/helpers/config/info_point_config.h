/*
  ╦  ╔╗╔  ╔═╗  ╔═╗    ╔═╗  ╔═╗  ╦  ╔╗╔  ╔╦╗        ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗
  ║  ║║║  ╠╣   ║ ║    ╠═╝  ║ ║  ║  ║║║   ║         ║    ║ ║  ║║║  ╠╣   ║  ║ ╦
  ╩  ╝╚╝  ╚    ╚═╝    ╩    ╚═╝  ╩  ╝╚╝   ╩         ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _INFO_POINT_CONFIG_H_
#define _INFO_POINT_CONFIG_H_
  #include "config_parser.h"

  /***************************************************************************
  *                        CONFIGURATION STRUCTURE                           *
  ***************************************************************************/

  #ifndef INFO_POINT_MAX_BUFF
    #define INFO_POINT_MAX_BUFF 100
  #endif

  /* Structure used to hold configuration borrowed from the config file */
  typedef struct info_point_config {
    /* Configuration for network setting related */
    struct network_settings {
      char host[INFO_POINT_MAX_BUFF];	// The host on which the server should run
      unsigned int port;		// The port that the server should use
      unsigned int timeout;		// Timeout after which a connection should stop
    } ns;

    /* Configuration for connection setting related */
    struct connection_settings {
      unsigned int max_clients; // N° of clients that the server should accept
      unsigned int max_threads; // N° of threads that the server should use
    } cs;

    /* Configuration for database setting related */
    struct database_settings {
      char type[INFO_POINT_MAX_BUFF];		// Type of the specified database
      char database_name[INFO_POINT_MAX_BUFF];	// Name of the database to use
      char host[INFO_POINT_MAX_BUFF];		// Host of the running database
      char username[INFO_POINT_MAX_BUFF];	// Username credential
      char password[INFO_POINT_MAX_BUFF];	// Password credential
      unsigned int port;			// Port of the running database
    } ds;

    /* Configuration for logging setting related */
    struct logging_settings {
      char log_level[INFO_POINT_MAX_BUFF];	// Logging level
      char log_file[INFO_POINT_MAX_BUFF];	// File on which make logging operations
    } ls;

  } info_point_config;

  // Provide a config filled out with the given config file
  info_point_config* provide_config(const char*);

  // Provide a default configuration if no specified config_file is given
  info_point_config* provide_default_config();

  // Provide a function in order to print to a specified FILE the given configuration
  void cfg_pretty_print(const info_point_config*, FILE*);

#endif
