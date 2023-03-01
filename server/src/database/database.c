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

db_handler* db_init(){
  db_handler* db = malloc(sizeof(struct db_handler));
  // TODO: DB_HANDLER SETUP

  _m(_msginfo, "Database handler successfully created!");
  return db;
}

void db_kill(db_handler * db){
  _m(_msginfo, "Shutting down the database handler as requested");
  // TODO: Handle close -> https://mongoc.org/libmongoc/current/tutorial.html

  _m(_msgevent, "Done!");
  free(db);
}
