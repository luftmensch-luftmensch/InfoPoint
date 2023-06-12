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

#define _m(type, format, ...) _msgcategory(type, "DATABASE_HANDLER", format __VA_OPT__(,) __VA_ARGS__)

db_handler* init_db_handler(char* username, char* password, char* host, char* database_name) {
  db_handler* handler = malloc(sizeof(struct db_handler));
  bson_error_t error; // Error handler

  assert((strlen(username) + strlen(password) + strlen(host)) < sizeof(handler->settings.database_uri));

  _m(_msginfo, "[%s] (%s) Initializing settings for the handler", __FILE_NAME__, __func__);

  // Uri field initialization
  snprintf(handler->settings.database_uri, sizeof(handler->settings.database_uri), "mongodb://%s:%s@%s/authMechanism=SCRAM-SHA-256&authSource=admin", username, password, host); // mongodb://<username>:<password>@<host>

  // Collections identifier field initialization
  handler->settings.user_collection     = (char*) MONGO_DB_USER_COLLECTION_NAME;
  handler->settings.art_work_collection = (char*) MONGO_DB_ARTWORK_COLLECTION_NAME;

  // Database name field initialization
  handler->settings.database_name = database_name;
  

  _m(_msginfo, "[%s] (%s) Database Handler initialization", __FILE_NAME__, __func__);
  mongoc_init(); /* Required to initialize libmongoc's internals (It should be called only once!) */

  /// Initialization of mongo_db instance

  /* Safely create a MongoDB URI object from the given string */

  _m(_msginfo, "[%s] (%s) Parsing mongodb endpoint <%s>\n", __FILE_NAME__, __func__, handler->settings.database_uri);
  handler->instance.uri = mongoc_uri_new_with_error(handler->settings.database_uri, &error);
  if (!handler->instance.uri) {
    _m(_msgfatal, "[%s] (%s) Failed to parse URI <%s> Cause: %s\n", __FILE_NAME__, __func__, handler->settings.database_uri, error.message);
    exit(errno);
  }

  printf("Auth source %s - Auth mechanism: %s\n", mongoc_uri_get_auth_source(handler->instance.uri), mongoc_uri_get_auth_mechanism(handler->instance.uri));

  _m(_msginfo, "[%s] (%s) Database instance pool setup", __FILE_NAME__, __func__);
  handler->instance.pool = mongoc_client_pool_new(handler->instance.uri);
  if (!handler->instance.pool) {
    _m(_msgfatal, "[%s] (%s) Failed to setup mongodb pool", __FILE_NAME__, __func__);
    exit(errno);
  }

  _m(_msginfo, "[%s] (%s) Customizing options for the mongodb pool", __FILE_NAME__, __func__);

  // Configure how the C Driver reports errors (See https://mongoc.org/libmongoc/current/errors.html#errors-error-api-version)
  mongoc_client_pool_set_error_api(handler->instance.pool, 2);

  /*
   * Register the application name so we can track it in the profile logs
   * on the server. This can also be done from the URI (see other examples).
   */
  mongoc_client_pool_set_appname(handler->instance.pool, MONGO_DB_APP_NAME);

  _m(_msginfo, "[%s] (%s) Database handler successfully destroyed!", __FILE_NAME__, __func__);
  return handler;
}


void destroy_db_handler(db_handler* handler) {
  /*
    For some reason interal function of mongoc triggers valgrind about certain
    known leaks/still reachable in both OpenSSL and CyrusSASL in certain scenarios.
    These are intentional by the respective libraries and should be ignored.
    See https://github.com/mongodb/mongo-c-driver/blob/master/valgrind.suppressions
  */

  _m(_msginfo, "[%s] (%s) Shutting down the database handler as requested", __FILE_NAME__, __func__);

  _m(_msginfo, "[%s] (%s) Destroying client handler: <%s>", __FILE_NAME__, __func__, handler->instance.pool);
  mongoc_client_pool_destroy(handler->instance.pool);

  /* Release handlers and make clean up operation */
  _m(_msginfo, "[%s] (%s) Destroying URI handler: <%s>", __FILE_NAME__, __func__, handler->instance.uri);
  mongoc_uri_destroy(handler->instance.uri);

  /*
    From: https://jira.mongodb.org/browse/CDRIVER-549

    Valgrind and OpenSSL are known for not getting very well along.

    The specific block that is causing the "still reachable" above
    can we resolved by your application – but is not something we can
    do in mongoc automatically as it can be "dangerous" to do without
    knowing what exactly your application will do next (or even
    how/why you are calling mongoc_cleanup()).

    If you want to resolve this at your application level, you can
    call use the cleanup routines Jason mentions – but even so, it
    might not catch 100% of OpenSSL reachable blocks (even though the
    one above would go away, another one might show up).
    Due to the nature of OpenSSL being very security sensitive, we
    would prefer not to aggressively attempt to cleanup every last
    byte which OpenSSL itself does not cleanup in normal
    circumstances. Doing so could easily cause more harm then good.

    We provide our own valgrind suppression file which we use for our
    testing.
    These are things that there isn't actually anything we can do to
    fix.
    See:
    https://github.com/mongodb/mongo-c-driver/blob/master/valgrind.suppressions
  */
  mongoc_cleanup();
  _m(_msghighlight, "[%s] (%s) Finishing mongoc cleanup", __FILE_NAME__, __func__);

  _m(_msgevent, "[%s] (%s) Done!", __FILE_NAME__, __func__);
  free(handler);
}
