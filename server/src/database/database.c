/*
  ╔╦╗┌─┐┌┬┐┌─┐┌┐ ┌─┐┌─┐┌─┐
   ║║├─┤ │ ├─┤├┴┐├─┤└─┐├┤ 
  ═╩╝┴ ┴ ┴ ┴ ┴└─┘┴ ┴└─┘└─┘
  Autori:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )

*/

#include "database.h"
#include <stdio.h>
#include <stdlib.h>


#define _m_d(type, format, ...) _msgcategory(type, "DATABASE", format, ##__VA_ARGS__)
#define _m_d_h(type, format, ...) _msgcategory(type, "DATABASE_HANDLER", format, ##__VA_ARGS__)


// Specific Database function

mongo_db* _database_setup(const char* uri){
  mongo_db* db = malloc(sizeof(struct mongo_db));
  bson_error_t error;

  /* Safely create a MongoDB URI object from the given string */
  _m_d(_msginfo, "Parsing mongodb endpoint <%s>\n", MONGO_DB_URI);
  db -> uri = mongoc_uri_new_with_error(uri, &error);
  if (!db->uri) {
    _m_d(_msgfatal, "Failed to parse URI <%s>. Cause: <%s>", uri, error.message);
    perror("Database connection initialization: ");
    exit(errno);
  }

  /* Client instance creation */
  _m_d(_msginfo, "Database instance client setup");
  db ->client = mongoc_client_new_from_uri(db -> uri);
  if (!db->client) {
    _m_d(_msgfatal, "Failed to create a new client instance");
    perror("Client instance: ");
    exit(errno);
  }
  /*
   * Register the application name so we can track it in the profile logs
   * on the server. This can also be done from the URI (see other examples).
  */
  _m_d(_msginfo, "Registring application name: <%s>", MONGO_DB_APP_NAME);
  mongoc_client_set_appname(db -> client, MONGO_DB_APP_NAME);

  
  _m_d(_msginfo, "Accessing to <%s> database", MONGO_DB_NAME);
  db -> database = mongoc_client_get_database(db -> client, MONGO_DB_NAME);

  _m_d(_msginfo, "Done!");

  return db;  
}

// Specific Database Handler function

db_handler* db_init(const char* uri){
  db_handler* db = malloc(sizeof(struct db_handler));

  /* Required to initialize libmongoc's internals (It should be called only once!) */
  _m_d_h(_msginfo, "Database Handler initialization");
  mongoc_init ();

  db -> database = _database_setup(uri);
  _m_d_h(_msginfo, "Database handler successfully created!");
  return db;
}


void db_kill(db_handler * db){
  _m_d_h(_msginfo, "Shutting down the database handler as requested");
  // TODO: Handle close -> https://mongoc.org/libmongoc/current/tutorial.html
  /* Release handlers and make clean up operation */
  _m_d_h(_msginfo, "Destroying collections <%s>, <%s>", MONGO_DB_CLIENT_COLLECTION_NAME, MONGO_DB_ARTWORK_COLLECTION_NAME);
  // TODO: Handle collections
  
  _m_d_h(_msginfo, "Destroying database handler: <%s>", MONGO_DB_NAME);
  mongoc_database_destroy(db->database->database);

  _m_d_h(_msginfo, "Destroying URI handler: <%s>", MONGO_DB_URI);
  mongoc_uri_destroy(db ->database->uri);

  _m_d_h(_msginfo, "Destroying client handler: <%s>", db->database->client);
  mongoc_client_destroy(db ->database->client);

  _m_d_h(_msghighlight, "Finishing cleanup");
  mongoc_cleanup ();

  _m_d_h(_msgevent, "Done!");
  
  free(db);
}
