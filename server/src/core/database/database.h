/*
  ╔╦╗┌─┐┌┬┐┌─┐┌┐ ┌─┐┌─┐┌─┐
   ║║├─┤ │ ├─┤├┴┐├─┤└─┐├┤ 
  ═╩╝┴ ┴ ┴ ┴ ┴└─┘┴ ┴└─┘└─┘
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/
#ifndef _DATABASE_H_
#define _DATABASE_H_

  #include <mongoc/mongoc.h>

  #include "../../infrastructure/logging/logging.h"
  #include "../../infrastructure/utility/utility.h"

  /** Global variables used to connect to the mongodb instance */

  #ifndef MONGO_DB_APP_NAME
      #define MONGO_DB_APP_NAME "InfoPoint App"
  #endif

  /* Database collection name */
  #ifndef MONGO_DB_USER_COLLECTION_NAME
      #define MONGO_DB_USER_COLLECTION_NAME "user"
  #endif

  #ifndef MONGO_DB_ARTWORK_COLLECTION_NAME
      #define MONGO_DB_ARTWORK_COLLECTION_NAME "artwork"
  #endif

  typedef struct db_handler {
    struct instance {
      mongoc_client_pool_t* pool;	/* Connection pool for multi-threaded programs */
      /* mongoc_client_t* client;		/\* Client to the mongodb instance *\/ */
      mongoc_uri_t* uri;		/* Abstraction on top of the MongoDB connection URI format */

      //mongoc_cursor_t* cursor;
      //bson_error_t error;
      //mongoc_database_t* database;
    } instance;

    /**
     * Structure representing information used to:
     * Connect & authenticate to a given mongodb instance
     * Do basic operation with the speciefied documents used by the service
     */
    struct mongo_db_settings {
      char* database_name;		/* Database name identifier */
      char  database_uri[100];		/* String used to connect to the mongodb instance */
      char* user_collection;		/* Identifier of the collection used to store & retrieve data of the users */
      char* art_work_collection;	/* Identifier of the collection used to store & retrieve data of the artworks */
    } settings;

  } db_handler;

  // Database Handler functions
  db_handler* init_db_handler(char*, char*, char*, char*);
  void destroy_db_handler(db_handler*);
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
