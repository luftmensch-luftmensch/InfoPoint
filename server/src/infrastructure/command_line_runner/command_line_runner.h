/*
  ╔═╗  ╔═╗  ╔╦╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗        ╦    ╦  ╔╗╔  ╔═╗        ╦═╗  ╦ ╦  ╔╗╔  ╔╗╔  ╔═╗  ╦═╗
  ║    ║ ║  ║║║  ║║║  ╠═╣  ║║║   ║║        ║    ║  ║║║  ║╣         ╠╦╝  ║ ║  ║║║  ║║║  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╩ ╩  ╩ ╩  ╩ ╩  ╝╚╝  ═╩╝        ╩═╝  ╩  ╝╚╝  ╚═╝        ╩╚═  ╚═╝  ╝╚╝  ╝╚╝  ╚═╝  ╩╚═
		  A wrapper around argp unix-style argument vector parser
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _COMMAND_LINE_RUNNER_H_
#define _COMMAND_LINE_RUNNER_H_

  #include <argp.h>
  #include <stdlib.h>
  #include "../logging/logging.h"
  
  /* Used by main to communicate with parse_opt. */
  typedef struct info_point_arguments {
    char** values;	/* [string...] */
    char* config_file;	/* Flag to indicate the config file to use (-c --config) */
    bool file_defined;	/* Check if the file is defined */
    int repeat_count;     /* count arg to ‘--repeat’ */
    /* TODO: Add other options to parse here if needed */
  } info_point_arguments;

  /* Wrapper around the argp_parse */
  char* parse_command_line_arguments(int, char**);

#endif
