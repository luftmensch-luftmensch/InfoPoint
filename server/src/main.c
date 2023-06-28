/*
  ╦  ╔╗╔  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╦  ╔╗╔  ╔╦╗
  ║  ║║║  ╠╣   ║ ║  ╠═╝  ║ ║  ║  ║║║   ║ 
  ╩  ╝╚╝  ╚    ╚═╝  ╩    ╚═╝  ╩  ╝╚╝   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/


#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

#include "core/server/server.h"
#include "helpers/logging/logging.h"
#include "helpers/logging/welcome_message.h"

#include "helpers/config/info_point_config.h"
#include "helpers/command_line_runner/command_line_runner.h"
#include "helpers/utility/utility.h"
#include "core/payload/payload.h"

int main(int argc, char** argv){
  // Welcome message
  fprintf(stdout, ANSI_COLOR_BMAGENTA "%s" ANSI_COLOR_RESET "\n", welcome_msg);
  
  // Parse command line arguments
  char* config_file = parse_command_line_arguments(argc, argv);

  /*
    Initialize the configuration structure based on how the user invoke the server:
    + If no config file is passed (server invoked with the -d flag) -> Populate the configuration using a default one
    + If a config file is passed (server invoked with the -c <FILE>) -> Populate the configuration using the given <FILE>
  */
  info_point_config* cfg = (config_file != NULL) ? provide_config(config_file) : provide_default_config();

  // Show the settings getted from the file
  cfg_pretty_print(cfg, stdout);


  server* s = init_server(cfg->ns.port, cfg->cs.max_clients);

  /* Finally free the cfg, as we no more need it */
  free(cfg);

  destroy_server(s);

  // const char* input ="CALL,EXPECTED,v3,v4,v5<>w1,w2,w3,w4,w5<>x1,x2,x3,x4<>y1,y2,y3,y4,y5,y6";

  // parse_data(input, "<>", ",");
}
