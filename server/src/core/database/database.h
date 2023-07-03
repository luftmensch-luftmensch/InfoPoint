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

  #ifndef MONGO_DB_COLLECTION_DATA_MAX_SIZE
    #define MONGO_DB_COLLECTION_DATA_MAX_SIZE 128
  #endif

  #ifndef REGEX_NICKNAME
    /**
     * User nickname boundaries:
     * 1. Has to start with an alphanumeric;
     * 2. At least two characters;
     * 3. Has to end with an alphanumeric
    */
    #define REGEX_NICKNAME "^[a-zA-Z0-9]+[_@#]?[a-zA-Z0-9]+$"
  #endif

  typedef struct db_handler {
    struct instance {
      mongoc_client_pool_t* pool;	/* Connection pool for multi-threaded programs */
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
      char  name[100];			/* Database name identifier */
      char  database_uri[100];		/* String used to connect to the mongodb instance */
      char* user_collection;		/* Identifier of the collection used to store & retrieve data of the users */
      char* art_work_collection;	/* Identifier of the collection used to store & retrieve data of the artworks */
    } settings;

  } db_handler;

  typedef enum document_type {
    ART_WORK,
    USER
  } document_type;

  /* ArtWork Collection structure */
  typedef struct art_work {
    char* name;
    char* author;
    char* description;
  } art_work;

  /* User Collection structure */
  typedef struct user {
    char* id;
    char* name;
    char* password;
    char* level;
  } user;

  /** Database Handler constructor */
  db_handler* init_handler(char*, char*, char*, char*);

  /** Database Handler destructor */
  void destroy_handler(db_handler*);

  /** Collection population */
  bool populate_collection(mongoc_client_t*, char*, char*);

  /** Retrieve art works from the database */
  void retrieve_art_works(mongoc_client_t*, char*, char*);

  /** Check if a document is present */
  bool is_present(mongoc_client_t*, bson_t*, bson_t*, char*, char*);

  /** Insert a single document in a given collection */
  bool insert_single(bson_t*, mongoc_client_t*, char*, char*);

  /** Helper method to parse a given bson_t to a common payload in form of an artwork */
  payload_t* parse_bson_as_artwork(const bson_t*);

  /** Helper method to parse a given bson_t to a common payload in form of an user */
  payload_t* parse_bson_as_user(const bson_t*);

  /** Helper method to test if the connection with the database is valid or not in order to inform the user */
  bool test_connection(mongoc_client_t*);
#endif
