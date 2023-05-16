/*
  ╔╦╗┌─┐┌┬┐┌─┐┌┐ ┌─┐┌─┐┌─┐
   ║║├─┤ │ ├─┤├┴┐├─┤└─┐├┤ 
  ═╩╝┴ ┴ ┴ ┴ ┴└─┘┴ ┴└─┘└─┘
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <stdio.h>
#include <stdlib.h>

#include "database.h"

#define _m_db(type, format, ...) _msgcategory(type, "DATABASE_HANDLER", format, ##__VA_ARGS__)

db_handler* init_db_handler(char* username, char* password, char* host, char* database_name) {
  db_handler* handler = malloc(sizeof(struct db_handler));

  _m_db(_msginfo, "Initializing settings for the handler");

  // Uri field initialization
  snprintf(handler->settings.database_uri, sizeof(handler->settings.database_uri), "mongodb://%s:%s@%s", username, password, host); // mongodb://<username>:<password>@<host>

  // Collections identifier field initialization
  handler->settings.user_collection     = (char*) MONGO_DB_USER_COLLECTION_NAME;
  handler->settings.art_work_collection = (char*) MONGO_DB_ARTWORK_COLLECTION_NAME;

  // Database name field initialization
  handler->settings.database_name = database_name;

  /* Required to initialize libmongoc's internals (It should be called only once!) */
  _m_db(_msginfo, "Database Handler initialization");
  mongoc_init();

  /// Initialization of mongo_db instance

  /* Safely create a MongoDB URI object from the given string */

  _m_db(_msginfo, "Parsing mongodb endpoint <%s>\n", handler->settings.database_uri);
  handler->instance.uri = mongoc_uri_new(handler->settings.database_uri); // TODO: Substitute with `mongoc_uri_new_with_error`
  if (!handler->instance.uri) {
    _m_db(_msgfatal, "[%s] (%s) Failed to parse URI <%s>", __FILE_NAME__, __func__, handler->settings.database_uri);
    exit(errno);
  }

  // printf("Auth source: %s\n", mongoc_uri_get_auth_mechanism(handler->instance.uri));

  _m_db(_msginfo, "Database instance pool setup");
  handler->instance.pool = mongoc_client_pool_new(handler->instance.uri);
  if (!handler->instance.pool) {
    _m_db(_msgfatal, "[%s] (%s) Failed to setup mongodb pool", __FILE_NAME__, __func__);
    exit(errno);
  }

  _m_db(_msginfo, "Customizing options for the mongodb pool");

  // Configure how the C Driver reports errors (See https://mongoc.org/libmongoc/1.14.0/errors.html#errors-error-api-version)
  mongoc_client_pool_set_error_api(handler->instance.pool, 2);

  /*
   * Register the application name so we can track it in the profile logs
   * on the server. This can also be done from the URI (see other examples).
   */
  mongoc_client_pool_set_appname(handler->instance.pool, MONGO_DB_APP_NAME);

  _m_db(_msginfo, "Database handler successfully created!");
  return handler;
}


void destroy_db_handler(db_handler* handler) {
  /*
    For some reason interal function of mongoc triggers valgrind about certain
    known leaks/still reachable in both OpenSSL and CyrusSASL in certain scenarios.
    These are intentional by the respective libraries and should be ignored.
    See https://github.com/mongodb/mongo-c-driver/blob/master/valgrind.suppressions
  */

  _m_db(_msginfo, "Shutting down the database handler as requested");

  _m_db(_msginfo, "Destroying client handler: <%s>", handler->instance.pool);
  mongoc_client_pool_destroy(handler->instance.pool);

  /* Release handlers and make clean up operation */
  _m_db(_msginfo, "Destroying URI handler: <%s>", handler->instance.uri);
  mongoc_uri_destroy(handler->instance.uri);

  mongoc_cleanup();
  _m_db(_msghighlight, "Finishing cleanup");

  _m_db(_msgevent, "Done!");
  free(handler);
}
