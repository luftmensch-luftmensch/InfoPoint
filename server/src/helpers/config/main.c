
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// #include "config.h"
#include "info_point_config.h"

/* void test(char* val) { */

/*   config* cfg = NULL; */
/*   //double port; */
/*   unsigned int port; */

/*   if(read_file(val, &cfg) != CONFIG_OK) { */
    
/*     fprintf(stderr, "Failed to parse file_name"); */
/*   } */
/*   /\* print_config_settings(cfg, stdout); *\/ */

/*   /\* print_config(cfg, stdout); *\/ */
  
/*   char s[1024]; */

/*   read_str_from_cfg(cfg, "network", "host", s, sizeof(s), "127.0.0.1"); */

/*   read_uint_from_cfg(cfg, "network", "port", &port, 8080); */

/*   printf("Network: Host <%s>, Port -> <%d>\n", s, port); */

/*   if(strcmp("localhost", s) == 0){ */
/*     printf("ALL DONE"); */
    
/*   } */

/*   destroy_config(cfg); */
  
/* } */

int main(int argc, char** argv) {
  info_point_config* cfg = provide_config(argv[1]);

  printf("[Network] Host -> <%s>, Port -> <%d>, Timeout -> <%d>\n", cfg->ns.host, cfg->ns.port, cfg->ns.timeout);
  printf("[Connections] Max Clients -> <%d>, Max Threads -> <%d>\n\n", cfg->cs.max_clients, cfg->cs.max_threads);
  printf("[Database] Type -> <%s>, Host -> <%s>, Port -> <%d>\n", cfg->ds.type, cfg->ds.host, cfg->ds.port);
  printf("[Logging] Log Level -> <%s>, Log File -> <%s>\n\n", cfg->ls.log_level, cfg->ls.log_file);

  free(cfg);
  /* test(argv[1]); */

  /* config* cfg = NULL; */
  /* //double port; */
  /* unsigned int port; */

  /* if(read_file(argv[1], &cfg) != CONFIG_OK) { */
    
  /*   fprintf(stderr, "Failed to parse file_name"); */
  /* } */
  /* /\* print_config_settings(cfg, stdout); *\/ */

  /* /\* print_config(cfg, stdout); *\/ */
  
  /* char s[1024]; */

  /* read_str_from_cfg(cfg, "network", "host", s, sizeof(s), "127.0.0.1"); */

  /* read_uint_from_cfg(cfg, "network", "port", &port, 8080); */

  /* printf("Network: Host <%s>, Port -> <%d>\n", s, port); */

  /* if(strcmp("localhost", s) == 0){ */
  /*   printf("ALL DONE"); */
    
  /* } */

  /* destroy_config(cfg); */
  
}
