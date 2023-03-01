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
#include <stdlib.h>

#define _m(type, format, ...) _msgcategory(type, "DATABASE", format, ##__VA_ARGS__)

db_handler* db_init(const char* uri){
  db_handler* db = malloc(sizeof(struct db_handler));

  /* Required to initialize libmongoc's internals (It should be called only once!) */
  mongoc_init ();

  //db -> uri = mongoc_uri_new_with_error(uri, &error)

  _m(_msginfo, "Database handler successfully created!");
  return db;
}

void db_kill(db_handler * db){
  _m(_msginfo, "Shutting down the database handler as requested");
  // TODO: Handle close -> https://mongoc.org/libmongoc/current/tutorial.html

  _m(_msgevent, "Done!");
  free(db);
}
