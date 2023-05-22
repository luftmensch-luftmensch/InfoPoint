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

  #include "../../helpers/logging/logging.h"
  #include "../../helpers/utility/utility.h"
  #include "../payload/payload.h"

  /** Global variables used to connect to the mongodb instance */

  #ifndef MONGO_DB_APP_NAME
      #define MONGO_DB_APP_NAME "InfoPoint App"
  #endif

  /* Database collections name */
  #ifndef MONGO_DB_USER_COLLECTION_NAME
      #define MONGO_DB_USER_COLLECTION_NAME "user"
  #endif

  #ifndef MONGO_DB_ARTWORK_COLLECTION_NAME
      #define MONGO_DB_ARTWORK_COLLECTION_NAME "artwork"
  #endif

  typedef struct db_handler {
    struct instance {
      mongoc_client_pool_t* pool;	/* Connection pool for multi-threaded programs */
      // mongoc_client_t* client;	/* Client to the mongodb instance  */
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

  // Database Handler related functions
  db_handler* init_db_handler(char*, char*, char*, char*);
  void destroy_db_handler(db_handler*);

  /* Collection population */
  bool populate_collection();

  /* Retrieve a single document in a form of a payload */
  payload_t* retrieve_single();

  /* Insert a single document in a given collection */
  bool insert_single(payload_t*, char*);
  /* Update a single document in a given collection */
  bool update_single(payload_t*, char*);

  /* Remove a single document from a given collection */
  bool delete_single(char*, char*);
  /* Bulk remove from a given collection with a matching strategy */
  bool bulk_delete(char*, char*);

#endif
