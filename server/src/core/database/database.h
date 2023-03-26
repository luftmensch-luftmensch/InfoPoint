#ifndef _DATABASE_H_
#define _DATABASE_H_

  #include <mongoc/mongoc.h>

  #include "../../common/logging/logging.h"

  /** Global variables used to connect to the mongodb instance */

  /* Connection URI */
  #ifndef MONGO_DB_APP_NAME
      #define MONGO_DB_APP_NAME "InfoPoint App"
  #endif

  #ifndef MONGO_DB_URI
      #define MONGO_DB_URI "mongodb://localhost:27017"
  #endif

  /* Database collection name */
  #ifndef MONGO_DB_CLIENT_COLLECTION_NAME
      #define MONGO_DB_CLIENT_COLLECTION_NAME "client"
  #endif

  #ifndef MONGO_DB_ARTWORK_COLLECTION_NAME
      #define MONGO_DB_ARTWORK_COLLECTION_NAME "artwork"
  #endif

  /* Database name */
  #ifndef MONGO_DB_NAME
      #define MONGO_DB_NAME "info-point"
  #endif

  /* Database user */
  #ifndef MONGO_DB_USERNAME
      #define MONGO_DB_USERNAME "admin"
  #endif

  /* Database password for the user */
  #ifndef MONGO_DB_PASSWORD
      #define MONGO_DB_PASSWORD "password"
  #endif

  typedef struct mongo_db {
    mongoc_uri_t* uri;
    mongoc_database_t* database;

    // Client to the mongodb instance
    mongoc_client_t* client;
  } mongo_db;

  typedef struct db_handler {
    mongo_db* database;
    mongoc_cursor_t* cursor;
    bson_error_t error;

  } db_handler;

  // Database Handler functions
  db_handler* db_init();
  void db_kill(db_handler*);
  // TODO: Change return type
  void retrieve_single();
  void retrieve_all();
  void fillCollection();
  void retrieve_key();

  // Client data related
  void add_client();
  void remove_client();
  void update_client();

#endif
