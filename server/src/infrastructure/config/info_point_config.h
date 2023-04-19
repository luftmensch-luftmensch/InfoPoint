/*
  ╦  ╔╗╔  ╔═╗  ╔═╗    ╔═╗  ╔═╗  ╦  ╔╗╔  ╔╦╗        ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗
  ║  ║║║  ╠╣   ║ ║    ╠═╝  ║ ║  ║  ║║║   ║         ║    ║ ║  ║║║  ╠╣   ║  ║ ╦
  ╩  ╝╚╝  ╚    ╚═╝    ╩    ╚═╝  ╩  ╝╚╝   ╩         ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _INFO_POINT_CONFIG_H_
#define _INFO_POINT_CONFIG_H_
  #include <stdint.h>
  #include "config_parser.h"

  /***************************************************************************
  *                        CONFIGURATION STRUCTURE                           *
  ***************************************************************************/

  /* Structure used to hold configuration borrowed from the config file */
  typedef struct info_point_config {
    /* Configuration for network setting related */
    struct network_settings {
      char host[100];		// The host on which the server should run
      unsigned int port;	// The port that the server should use
      unsigned int timeout;	// Timeout after which a connection should stop
    } ns;

    /* Configuration for connection setting related */
    struct connection_settings {
      unsigned int max_clients; // N° of clients that the server should accept
      unsigned int max_threads; // N° of threads that the server should use
    } cs;

    /* /\* Configuration for database setting related *\/ */
    struct database_settings {
      char type[100];	 // Type of the specified database
      char host[100];    // Host of the running database
      unsigned int port; // Port of the running database
    } ds;

    /* /\* Configuration for logging setting related *\/ */
    struct logging_settings {
      char log_level[100]; // Logging level
      char log_file[100];  // File on which make logging operations
    } ls;

  } info_point_config;

  // Provide a config filled out with the given config file or a default one in case something went wrong when loading/parsing the config file
  info_point_config* provide_config(const char*);


#endif
