/*
  ╦  ╔╗╔  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╦  ╔╗╔  ╔╦╗
  ║  ║║║  ╠╣   ║ ║  ╠═╝  ║ ║  ║  ║║║   ║ 
  ╩  ╝╚╝  ╚    ╚═╝  ╩    ╚═╝  ╩  ╝╚╝   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/


#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

#include "core/server/server.h"
#include "infrastructure/logging/logging.h"
#include "infrastructure/logging/welcome_message.h"

#include "infrastructure/pool/thread_pool.h"
#include "infrastructure/config/info_point_config.h"
#include "infrastructure/command_line_runner/command_line_runner.h"

// void task(void *arg){
//     printf("Thread #%u working on %d\n", (int)pthread_self(), (int)(uintptr_t) arg);
// }

int main(int argc, char** argv){
  if (argc < 1) {
    fprintf(stderr, "Error");
  }
  // Welcome message
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET , welcome_msg);

  char* config_file = parse_command_line_arguments(argc, argv);

  if (config_file != NULL)
    printf("%s", config_file);

  //server* s = init_server(9090, 10);

  //printf("%lu\n", s->conn_count);
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

  // info_point_config* cfg = provide_config(argv[1]);

  // printf("[Network] Host -> <%s>, Port -> <%d>, Timeout -> <%d>\n", cfg->ns.host, cfg->ns.port, cfg->ns.timeout);
  // printf("[Connections] Max Clients -> <%d>, Max Threads -> <%d>\n\n", cfg->cs.max_clients, cfg->cs.max_threads);
  // printf("[Database] Type -> <%s>, Host -> <%s>, Port -> <%d>\n", cfg->ds.type, cfg->ds.host, cfg->ds.port);
  // printf("[Logging] Log Level -> <%s>, Log File -> <%s>\n\n", cfg->ls.log_level, cfg->ls.log_file);

  // free(cfg);

}
