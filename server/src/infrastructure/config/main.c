#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"


int main(int argc, char** argv) {
  config* cfg = provide_config(argv[1]);
  //config* cfg = provide_default_config();
  if (strcmp(cfg->ns.host, "localhost") == 0)  {
    printf("All done\n");
    printf("%s", cfg->ns.host);
  }
  free(cfg);
}

//int main(int argc, char** argv) {
//  ini_parser* ini = init_parser(argv[1]); // Parse the given file
//  config* cfg = malloc(sizeof(struct config));
//
//  /* Retrieve values form the parser */
//
//  // NETWORK
//  char* host    = (char*) get_value(ini, "network", "host");
//  char* port    = (char*) get_value(ini, "network", "port");
//  char* timeout = (char*) get_value(ini, "network", "timeout");
//
//  // CONNECTIONS
//  char* max_clients = (char*) get_value(ini, "connections", "max_clients");
//  char* max_threads = (char*) get_value(ini, "connections", "max_threads");
//
//  // LOGGING
//  char* log_level = (char*) get_value(ini, "logging", "log_level");
//  char* log_file = (char*) get_value(ini, "logging", "log_file");
//
//  // Network configuration settings
//  cfg->ns.host = (host != NULL) ? host : "127.0.0.1";
//  cfg->ns.port = (port != NULL) ? port : "8080";
//  cfg->ns.timeout = (timeout != NULL) ? timeout : "0";
//
//  //// Connections configuration settings
//  cfg->cs.max_clients = (max_clients != NULL) ? max_clients : "10";
//  cfg->cs.max_threads = (max_threads != NULL) ? max_threads : "10";
//  //
//  //// Logging configuration settings
//  cfg->ls.log_level = (log_level != NULL) ? log_level : "normal";
//  cfg->ls.log_file = (log_file != NULL) ? log_file : "stderr";
//
//  printf("%s\n", cfg->ls.log_file);
//
//  destroy_parser(ini);
//
//  free(cfg);
//}
