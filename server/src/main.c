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

#include "helpers/pool/thread_pool.h"
#include "helpers/config/info_point_config.h"
#include "helpers/command_line_runner/command_line_runner.h"
#include "helpers/utility/utility.h"
#include "core/database/database.h"

// void task(void *arg){
//     printf("Thread #%u working on %d\n", (int)pthread_self(), (int)(uintptr_t) arg);
// }

#define _tmp(type, format, ...) _msgcategory(type, " SERVER ", format __VA_OPT__(,) __VA_ARGS__)

#define _m(type, format, ...) _msgcategory(type, "SERVER", format, ##__VA_ARGS__)

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

  /* // Finally free the cfg, as we no more need it */
  free(cfg);

  server* s = init_server(9090, 10);

  destroy_server(s);
  /* puts("Making threadpool with 4 threads"); */
  /* struct thread_pool* thpool = init_thread_pool(4); */

  /* puts("Adding 40 tasks to threadpool"); */
  /* int i; */
  /* for (i=0; i<40; i++){ */
  /*   add_work_to_thread_pool(thpool, task, (void*)(uintptr_t)i); */
  /* }; */

  /* await_thread_pool(thpool); */
  /* puts("Killing threadpool"); */
  /* destroy_thread_pool(thpool); */


  /* printf("%s\n", buff); */

  /* db_handler* database = init_db_handler("admin", "password", "localhost:27017", "noesys"); */

  /* printf("%s %s %s\n", database->settings.user_collection, database->settings.art_work_collection, database->settings.database_name); */


  /* destroy_db_handler(database); */
  log_debug(ANSI_COLOR_RED "%s %s %d %d" ANSI_COLOR_RESET "\n" , __FILE__, __func__, 5, 7);

  _tmp(_msgevent, "%d\n", 10);
  _tmp(_msgevent, "Goodbye!", );
}
