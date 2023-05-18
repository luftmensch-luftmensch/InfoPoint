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
#include "info_point_config.h"

info_point_config* provide_config(const char* file_name) {
  info_point_config* info_point_cfg = malloc(sizeof(info_point_config));
  config_parser* parser = NULL;
  if(read_file(file_name, &parser) != CONFIG_OK) {
    fprintf(stderr, "[%s] (%s) Failed to parse %s", __FILE__, __func__, file_name);
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
  read_str_from_cfg(parser, "database", "host", info_point_cfg->ds.host, sizeof(info_point_cfg->ds.host), "undefined");
  read_str_from_cfg(parser, "database", "auth_mechanism", info_point_cfg->ds.auth_mechanism, sizeof(info_point_cfg->ds.auth_mechanism), "undefined");

  read_uint_from_cfg(parser, "database", "port", &info_point_cfg->ds.port, 1234);

  destroy_config(parser);
  return info_point_cfg;
}
