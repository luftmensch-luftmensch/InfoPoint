/*
  ╦  ╔╗╔  ╔═╗  ╔═╗    ╔═╗  ╔═╗  ╦  ╔╗╔  ╔╦╗        ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗
  ║  ║║║  ╠╣   ║ ║    ╠═╝  ║ ║  ║  ║║║   ║         ║    ║ ║  ║║║  ╠╣   ║  ║ ╦
  ╩  ╝╚╝  ╚    ╚═╝    ╩    ╚═╝  ╩  ╝╚╝   ╩         ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <stdlib.h>
#include <string.h>
#include "info_point_config.h"

info_point_config* provide_config(const char* file_name) {
  info_point_config* info_point_cfg = malloc(sizeof(info_point_config));
  config_parser* parser = NULL;
  if(read_file(file_name, &parser) != CONFIG_OK) {
    fprintf(stderr, "[%s] (%s) Failed to parse %s", __FILE__, __func__, file_name);
    free(info_point_cfg);
    return NULL;
  }

  /* [Network] Retriving config options fields from the given config file */
  read_str_from_cfg (parser, "network", "host",    info_point_cfg->ns.host, sizeof(info_point_cfg->ns.host), "127.0.0.1");
  read_uint_from_cfg(parser, "network", "port",    &info_point_cfg->ns.port, 8080);
  read_uint_from_cfg(parser, "network", "timeout", &info_point_cfg->ns.timeout, 10);

  /* [Connections] Retriving config options fields from the given config file */
  read_uint_from_cfg(parser, "connections", "max_clients", &info_point_cfg->cs.max_clients, 10);
  read_uint_from_cfg(parser, "connections", "max_threads", &info_point_cfg->cs.max_threads, 10);

  /* [Logging] Retriving config options fields from the given config file */

  read_str_from_cfg(parser, "logging", "log_level", info_point_cfg->ls.log_level, sizeof(info_point_cfg->ls.log_level), "warning");
  read_str_from_cfg(parser, "logging", "log_file",  info_point_cfg->ls.log_file, sizeof(info_point_cfg->ls.log_file), "stderr");

  /* [Database] Retriving config options fields from the given config file */
  read_str_from_cfg(parser, "database", "type", info_point_cfg->ds.type, sizeof(info_point_cfg->ds.type), "undefined");
  read_str_from_cfg(parser, "database", "name", info_point_cfg->ds.database_name, sizeof(info_point_cfg->ds.database_name), "undefined");
  read_str_from_cfg(parser, "database", "host", info_point_cfg->ds.host, sizeof(info_point_cfg->ds.host), "undefined");
  read_str_from_cfg(parser, "database", "username", info_point_cfg->ds.username, sizeof(info_point_cfg->ds.username), "undefined");
  read_str_from_cfg(parser, "database", "password", info_point_cfg->ds.password, sizeof(info_point_cfg->ds.password), "undefined");

  read_uint_from_cfg(parser, "database", "port", &info_point_cfg->ds.port, 1234);

  destroy_config(parser);
  return info_point_cfg;
}

info_point_config* provide_default_config() {
  info_point_config __default_cfg = {
    .ns = {
      .host = "localhost",
      .port = 9090,
      .timeout = 10,
    },
    .cs = {
      .max_clients = 100,
      .max_threads = 100,
    },
    .ds = {
      .type = "mongodb",
      .host = "localhost",
      .username = "admin",
      .password = "password",
      .database_name = "info",
      .port = 27017,
    },
    .ls = {
      .log_level = "warning",
      .log_file = "stdout",
    }
  };

  info_point_config* cfg = malloc(sizeof(info_point_config));
  memcpy((void*) cfg, (void*) &__default_cfg, sizeof(__default_cfg));
  return cfg;
}

void cfg_pretty_print(const info_point_config* cfg, FILE* file) {
  fprintf(file, "### Networking\n\tHost -> %s, Port -> %d, Timeout -> %d\n\n", cfg->ns.host, cfg->ns.port, cfg->ns.timeout);
  fprintf(file, "### Connections\n\tMax Clients -> %d, Max Threads ->  %d\n\n", cfg->cs.max_clients, cfg->cs.max_threads);
  fprintf(file, "### Database\n\tType -> %s, Host -> %s, Username -> %s, Password -> %s, Database Name -> %s, Port -> %d\n\n", cfg->ds.type, cfg->ds.host, cfg->ds.username, cfg->ds.password, cfg->ds.database_name, cfg->ds.port);
  fprintf(file, "### Logging\n\tLog Level - %s, Log File - %s\n\n", cfg->ls.log_level, cfg->ls.log_file);
}
