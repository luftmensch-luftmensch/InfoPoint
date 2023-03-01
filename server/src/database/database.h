#ifndef InfoPoint_Database
#define InfoPoint_Database

  #include "../utils/common/utils.h"
  /** Global variables used to connect to the mongodb instance */

  /* Connection URI */
  #ifndef MONGO_DB_URI
      #define MONGO_DB_URI "mongodb://localhost:27017"
  #endif

  /* Database collection name */
  #ifndef MONGO_DB_COLLECTION_NAME
      #define MONGO_DB_COLLECTION_NAME "InfoPoint"
  #endif

  /* Database user */
  #ifndef MONGO_DB_USERNAME
      #define MONGO_DB_USERNAME "admin"
  #endif

  /* Database password for the user */
  #ifndef MONGO_DB_PASSWORD
      #define MONGO_DB_PASSWORD "password"
  #endif

typedef struct db_handler {
  // TODO: Add variables
  const char* uri;

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
