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

#include "../../helpers/base/macros.h"
#include "../message/message.h"

#define _m(type, format, ...) _msgcategory(type, "DATABASE_HANDLER", format __VA_OPT__(,) __VA_ARGS__)

/* Helpers function for art_work & user */
static void destroy_art_work(art_work*);
static void destroy_user(user*);

db_handler* init_handler(char* username, char* password, char* host, char* database_name) {
  db_handler* handler = malloc(sizeof(struct db_handler));
  bson_error_t error; // Error handler

  assert((strlen(username) + strlen(password) + strlen(host)) < sizeof(handler->settings.database_uri));

  _m(_msginfo, "[%s] (%s) Initializing settings for the handler", __FILE_NAME__, __func__);

  // Uri field initialization
  snprintf(handler->settings.database_uri, sizeof(handler->settings.database_uri), "mongodb://%s:%s@%s/", username, password, host); // mongodb://<username>:<password>@<host>

  // Collections identifier field initialization
  handler->settings.user_collection     = (char*) MONGO_DB_USER_COLLECTION_NAME;
  handler->settings.art_work_collection = (char*) MONGO_DB_ARTWORK_COLLECTION_NAME;

  // Database name field initialization
  assert((strlen(database_name) + 1) < sizeof(handler->settings.name));
  snprintf(handler->settings.name, sizeof(handler->settings.name), "%s", database_name);

  _m(_msginfo, "[%s] (%s) Database Handler initialization", __FILE_NAME__, __func__);
  mongoc_init(); /* Required to initialize libmongoc's internals (It should be called only once!) */

  /// Initialization of mongo_db instance

  /* Safely create a MongoDB URI object from the given string */

  _m(_msginfo, "[%s] (%s) Parsing mongodb endpoint <%s>", __FILE_NAME__, __func__, handler->settings.database_uri);
  handler->instance.uri = mongoc_uri_new_with_error(handler->settings.database_uri, &error);
  if (!handler->instance.uri) {
    _m(_msgfatal, "[%s] (%s) Failed to parse URI <%s> Cause: %s\n", __FILE_NAME__, __func__, handler->settings.database_uri, error.message);
    exit(errno);
  }

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

  _m(_msginfo, "[%s] (%s) Database handler successfully initialized!", __FILE_NAME__, __func__);
  return handler;
}

void destroy_handler(db_handler* handler) {
  /*
    For some reason interal function of mongoc triggers valgrind about certain
    known leaks/still reachable in both OpenSSL and CyrusSASL in certain scenarios.
    These are intentional by the respective libraries and should be ignored.
    See https://github.com/mongodb/mongo-c-driver/blob/master/valgrind.suppressions
  */

  _m(_msginfo, "[%s] (%s) Shutting down the database handler as requested", __FILE_NAME__, __func__);

  _m(_msginfo, "[%s] (%s) Destroying client handler...", __FILE_NAME__, __func__);
  mongoc_client_pool_destroy(handler->instance.pool);

  /* Release handlers and make clean up operation */
  _m(_msginfo, "[%s] (%s) Destroying URI handler...", __FILE_NAME__, __func__);
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

bool populate_collection(mongoc_client_t* client, char* database_name, char* collection_name) {
  // Custom entry used to populate the ArtWork collection
  art_work artworks[] = {	/* Name, Author, Date of Production, Description */
    {(char*) "Amore e Psiche",               (char*) "Antonio Canova",       (char*) "1787-1793", (char*) "Gruppo scultoreo commissionato dal colonello inglese John Campbell. Rappresenta in pieno lo stile neoclassico, mostrando i due protagonisti nel momento precedente all'azione del bacio."},

    {(char*) "Gli Amanti",                   (char*) "René Magritte",        (char*) "1928", (char*) "Il quadro raffigura due amanti che si baciano, con le teste coperte da un panno bianco. L'immagine parla di morte e di impossibilità di comunicare quasi a rappresentare un ultimo bacio da parte delle due figure"},

    {(char*) "La persistenza della memoria", (char*) "Salvador Dalì",        (char*) "1931", (char*) "L'opera surrealista mostra come lo scorrere del tempo non sia lo stesso per uomini, animali e vegetali tramite un paesaggio disabitato e privo di vegetazione ma popolato da diversi oggetti: un parallelepidedo, un ulivo senza foglie, un occhio addormentato e degli orologi."},

    {(char*) "Il Bacio",                     (char*) "Gustav Klimt",         (char*) "1907-1908", (char*) "L'opera rappresenta due amanti che si abbandonano ad un bacio intenso. Tema dominante è l'amore e le passioni umane rappresentato nel modo più semplice possibile."},

    {(char*) "La Giuditta",                  (char*) "Gustav Klimt",         (char*) "1901", (char*) "Tra le prime opere dell'artista, rappresenta l'eroina biblica utilizzando il volto di Adele Bloch-Bauer, esponente dell'alta società viennese. Indica la metafora del potere della seduzione delle donne che riesce a vincere anche la forza virile più bruta."},

    {(char*) "La Notte Stellata",            (char*) "Vincent Van Gogh",     (char*) "1889", (char*) "L'opera rappresenta ciò che si poteva vedere dalla finestra della stanza del manicomio in cui si trovava l'artista. Van Gogh manipola questa veduta trasformandola in una potente visione in cui poter far affiorare le sue emozioni, le sue paure e i suoi viaggi dell'anima."},

    {(char*) "Apollo e Dafne",               (char*) "Gian Lorenzo Bernini", (char*) "1622-1625", (char*) "Commissionata dal cardinale Scipione Caffarelli-Borghese, essa rappresenta l'istante in cui Apollo raggiunge la ninfa Dafne che per sfuggire al dio, si trasforma in pianta di alloro. L'opera, ricca di pathos, trasmette equilibrio ed armonia dovuto al gioco di luci ed ombre creato da Bernini."},

    {(char*) "Il David",                     (char*) "Michelangelo",         (char*) "1501-1504", (char*) "L'opera ritrae l'eroe biblico nel momento in cui affronta Golia. Considerato l'ideale di bellezza maschile indica il simbolo della Repubblica Fiorentina vigile e vittoriosa contro i nemici."},

    {(char*) "La Nascita di Venere",         (char*) "Sandro Botticelli",    (char*) "1482-1485", (char*) "Simbolo del Rinascimento italiano l'opera raffigura la dea emergere dal mare su una conchiglia, spinta dal soffio di Zefiro, mentre sulla riva Primavera le porge un manto. L'opera incarna l'ideale di bellezza femminile, con Simonetta Vespucci come musa ispiratrice per l'artista."},

    {(char*) "La Danza",                     (char*) "Henri Matisse",        (char*) "1909", (char*) "Simbolo del fauvismo e dell'arte moderna, l'opera rappresenta un gruppo di figure umane che si abbracciano e che danzano in una cerchia. I colori sono vivaci ed i contorni risultano stilizzati donando, cosi, un senso di movimento e vitalità."},

    {(char*) "Cristo Velato",                (char*) "Giuseppe Sanmartino",  (char*) "1753", (char*) "La statua raffigura il Cristo deposto, avvolto in un velo di marmo che sembra quasi traslucido, creando un effetto di delicatezza. L'opera è caratterizzata da una maestria tecnica straordinaria e una forte espressione emotiva, diventando un'icona del barocco napoletano."},
  };

  bson_t* documents[ARRAY_SIZE(artworks)];

  bson_error_t error; // Error handler

  // Inizialize the document
  for (size_t i = 0; i < ARRAY_SIZE(artworks); i++) {
    bson_oid_t oid;
    bson_oid_init (&oid, NULL);

    // { "_id" : { "$oid" : "<&oid>" }, "name" : <VALUE>, "author" : <VALUE>, "description" : <VALUE>, "date": <VALUE> }
    documents[i] = BCON_NEW("_id", BCON_OID(&oid),
			    "name", BCON_UTF8(artworks[i].name),
			    "author", BCON_UTF8(artworks[i].author),
			    "date", BCON_UTF8(artworks[i].date),
			    "description", BCON_UTF8(artworks[i].description));
  }

  // Retrieve the collection in which execute bulk insert
  mongoc_collection_t* collection = mongoc_client_get_collection(client, database_name, collection_name);

  // Insert multi checking for errors
  bool status = mongoc_collection_insert_many(collection, (const bson_t **) documents, ARRAY_SIZE(artworks), NULL, NULL, &error);

  if (!status) {
    _m(_msginfo, "[%s] (%s) Failed to populate the collection %s! Cause: %s\n", __FILE_NAME__, __func__, collection_name , error.message);
  }

  // Only for debug purpose (Decomment to show the structure of the artwork documents)
  for (size_t i = 0; i < ARRAY_SIZE(artworks); i++) {
    char* str;
    str = bson_as_canonical_extended_json (documents[i], NULL);
    printf("Item n° %zu: %s\n", i, str);
    bson_free(str);
  }

  /* Document cleanup */
  for (size_t i = 0; i < ARRAY_SIZE(artworks); i++)
    bson_destroy(documents[i]);

  /* Collection clenaup */
  mongoc_collection_destroy(collection);

  return status;
}

void retrieve_art_works(mongoc_client_t* client, char* database_name, char* collection_name, ssize_t fd) {
  bson_error_t error;

  // Retrieve the collection in which execute bulk insert
  mongoc_collection_t* collection = mongoc_client_get_collection(client, database_name, collection_name);

  bson_t* filter = BCON_NEW("name", BCON_REGEX("[^\n]+", "i")); /* Other regex: (.*?) */

  // bson_t* opts = BCON_NEW("limit", BCON_INT64(15));

  mongoc_cursor_t* cursor = mongoc_collection_find_with_opts(collection, filter, NULL, NULL);

  const bson_t* retrieved;

  while (mongoc_cursor_next(cursor, &retrieved)) {
    payload_t* p = parse_bson_as_artwork(retrieved);
    // printf("Payload: <%s> Size: <%zu> Len: <%zu>\n", (char*) p->data, sizeof(p->data), strlen(p->data));
    msg_send(fd, (char*) p->data, strlen(p->data), 0);
    free(p->data);
    free(p);
  }

  // msg_send(fd, "<>DONE<>", sizeof("<>DONE<>"), 0);

  if (mongoc_cursor_error(cursor, &error)) {
    _m(_msgwarn, "[%s] (%s) An error occurred! Cause: %s\n", __FILE_NAME__, __func__, error.message);
  }

  /* Query cleanup */
  bson_free(filter);
  // bson_free(opts);

  /* Collection clenaup */
  mongoc_collection_destroy(collection);

  /* Cursor cleanup */
  mongoc_cursor_destroy(cursor);

}


bool insert_single(mongoc_client_t* client, bson_t* document, char* database_name, char* collection_name) {
  mongoc_collection_t* collection = mongoc_client_get_collection(client, database_name, collection_name);

  bson_error_t error; // Error handler

  /* Insert the document & check for errors */
  // if (!mongoc_collection_insert_one(collection, document, NULL, NULL, &error)) {
  //   _m(_msginfo, "[%s] (%s) Failed to insert into collection %s! Cause: %s\n", __FILE_NAME__, __func__, collection_name , error.message);
  //   return false;
  // }

  if (!mongoc_collection_insert_one(collection, document, NULL, NULL, &error)) {
    _m(_msginfo, "[%s] (%s) Failed to insert into collection %s! Cause: %s\n", __FILE_NAME__, __func__, collection_name , error.message);
    return false;
  }

  /* Collection clenaup */
  mongoc_collection_destroy(collection);

  return true;
}

bool delete_single(mongoc_client_t* client, bson_t* document, char* database_name, char* collection_name) {
  mongoc_collection_t* collection = mongoc_client_get_collection(client, database_name, collection_name);

  bson_error_t error; // Error handler
  bson_t* opts = BCON_NEW("limit", BCON_INT64(1));

  if (!mongoc_collection_delete_one(collection, document, opts, NULL, &error)) {
    _m(_msginfo, "[%s] (%s) Failed to delete document from collection %s! Cause: %s\n", __FILE_NAME__, __func__, collection_name , error.message);
    return false;
  }

  /* Destroy options */
  bson_free(opts);

  /* Collection clenaup */
  mongoc_collection_destroy(collection);

  return true;
}

bool is_present(mongoc_client_t* client, bson_t* filter, bson_t* options, char* database_name, char* collection_name) {
  bson_error_t error;

  mongoc_collection_t* collection = mongoc_client_get_collection(client, database_name, collection_name);

  mongoc_cursor_t* cursor = mongoc_collection_find_with_opts(collection, filter, options, NULL);

  const bson_t* retrieved;
  if (!mongoc_cursor_next(cursor, &retrieved)) {
    _m(_msginfo, "[%s] (%s) Failed to found document!", __FILE_NAME__, __func__);
    return false;
  }

  if (mongoc_cursor_error(cursor, &error)) {
    _m(_msgwarn, "[%s] (%s) An error occurred! Cause: %s\n", __FILE_NAME__, __func__, error.message);
  }

  /* Cursor cleanup */
  mongoc_cursor_destroy(cursor);

  /* Collection clenaup */
  mongoc_collection_destroy(collection);
  return true;
}

payload_t* parse_bson_as_artwork(const bson_t* document) {
  if (document == NULL)
    return NULL;

  payload_t* payload = malloc(sizeof(struct payload_t));

  bson_iter_t iter;

  art_work* art = malloc(sizeof(struct art_work));

  if (bson_iter_init(&iter, document)) {
    while(bson_iter_next(&iter)) {
      const bson_value_t* value = bson_iter_value(&iter);
      if (strcmp(bson_iter_key(&iter), "_id") == 0) { /* TODO: Use this? */

      } else if (strcmp(bson_iter_key(&iter), "name") == 0) {
	art->name = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) art->name, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else if (strcmp(bson_iter_key(&iter), "author") == 0) {
	art->author = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) art->author, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else if (strcmp(bson_iter_key(&iter), "date") == 0) {
	art->date = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) art->date, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else if (strcmp(bson_iter_key(&iter), "description") == 0) {
	art->description = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) art->description, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else {
	_m(_msginfo, "[%s] (%s) Unknown key <%s> while parsing artwork document!", __FILE_NAME__, __func__, bson_iter_key(&iter));
      }
    }
  }
  size_t total_size = (strlen(art->name) + 1) + (strlen(art->author) + 1) + (strlen(art->date) + 1) +  (strlen(art->description) + 1) + 41; // Delimiters + key

  payload->data = malloc(total_size);
  payload->size = total_size;

  snprintf(payload->data, total_size, "<>NAME:%s<>AUTHOR:%s<>DATE:%s<>DESCRIPTION:%s<>\n", art->name, art->author, art->date, art->description);

  destroy_art_work(art);
  return payload;
}

payload_t* parse_bson_as_user(const bson_t* document) {
  if (document == NULL)
    return NULL;

  payload_t* payload = malloc(sizeof(struct payload_t));

  bson_iter_t iter;

  user* u = malloc(sizeof(struct user));

  if (bson_iter_init(&iter, document)) {
    while(bson_iter_next(&iter)) {
      const bson_value_t* value = bson_iter_value(&iter);
      if (strcmp(bson_iter_key(&iter), "_id") == 0) { /* TODO: Use this? */

      } else if (strcmp(bson_iter_key(&iter), "name") == 0) {
	u->name = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) u->name, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else if (strcmp(bson_iter_key(&iter), "password") == 0) {
	u->password = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) u->password, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else if (strcmp(bson_iter_key(&iter), "level") == 0) {
	u->level = malloc(sizeof(char) * (strlen(value->value.v_utf8.str) + 1));
	memcpy((void*) u->level, (void*) value->value.v_utf8.str, (strlen(value->value.v_utf8.str) + 1));
      } else {
	_m(_msginfo, "[%s] (%s) Unknown key <%s> while parsing user document!", __FILE_NAME__, __func__, bson_iter_key(&iter));
      }
    }
  }

  size_t total_size = (strlen(u->name) + 1) + (strlen(u->password) + 1) + (strlen(u->level) + 1) + 9;

  payload->data = malloc(total_size);
  payload->size = total_size;

  snprintf(payload->data, payload->size, "<>%s<>%s<>%s<>", u->name, u->password, u->level);

  destroy_user(u);

  return payload;
}


static void destroy_user(user* u) {
  if(!u) return;
  if (u->name) free(u->name);
  if (u->password) free(u->password);
  if (u->level) free(u->level);
  free(u);
}

static void destroy_art_work(art_work* art) {
  if (!art)
    return;

  if (art->name) free(art->name);
  if (art->author) free(art->author);
  if (art->description) free(art->description);
  free(art);
}

bool test_connection(mongoc_client_t* client) {
  /* Test if the connection is valid by pinging the database (because obv there is no native way to do it :\ ) */
  bson_error_t error;

  bson_t* ping = BCON_NEW("ping", BCON_INT32(1));
  bson_t reply;
  bool status;

  mongoc_database_t *database = mongoc_client_get_database(client, "admin");
  if (mongoc_database_command_simple(database, ping, NULL, &reply, &error)) {
    _m(_msginfo, "[%s] (%s) Successfully connected to mongodb instance!", __FILE_NAME__, __func__);
    status = true;
  } else {
    _m(_msginfo, "[%s] (%s) Failed to connect to mongodb instance! Cause: %s", __FILE_NAME__, __func__, error.message);
    status = false;
  }

  /* Cleanup operation */
  bson_free(ping);
  bson_destroy(&reply);
  mongoc_database_destroy(database);

  return status;
}

/**
 * Example of usage (is_present):
    ```
    bson_t* filter = BCON_NEW("name", BCON_UTF8("NAME1"));
    bson_t* opts = BCON_NEW("limit", BCON_INT64(1));

    bool status = is_present(client, filter, opts, s->handler->settings.name, s->handler->settings.art_work_collection);

    printf("Status: %d\n", status);

    bson_free(filter);
    bson_free(opts);
    ```

 * Example of usage (parse_bson_as_artwork):
    ```
    bson_t* doc = BCON_NEW("_id", BCON_INT32(0),
			   "name", BCON_UTF8("NAME"),
			   "author", BCON_UTF8("AUTHOR"),
			   "description", BCON_UTF8("DESCRIPTION"));

    bson_t* doc_u = BCON_NEW("_id", BCON_INT32(0),
			   "name", BCON_UTF8("NAME"),
			   "password", BCON_UTF8("PASSWORD"),
			   "level", BCON_UTF8("LEVEL"));

    payload_t* p = parse_bson_as_artwork(doc);

    printf("%s\n", (char*) p->data);

    free(p->data);
    free(p);

    payload_t* p_u = parse_bson_as_user(doc_u);

    printf("%s\n", (char*) p_u->data);

    free(p_u->data);
    free(p_u);

    bson_free(doc);
    bson_free(doc_u);
    ```

 * Example of usage (populate_collection):
    ```
    mongoc_client_t* client = mongoc_client_pool_pop(s->handler->instance.pool);

    bool status = populate_collection(client, s->handler->settings.name, s->handler->settings.art_work_collection);

    printf("Status: %d\n", status);

    mongoc_client_pool_push(s->handler->instance.pool, client);
    ```

 * Example of usage (retrieve_art_works):
    ```
    mongoc_client_t* client = mongoc_client_pool_pop(s->handler->instance.pool);
    retrieve_art_works(client, s->handler->settings.name, s->handler->settings.art_work_collection);
    mongoc_client_pool_push(s->handler->instance.pool, client);
    ```
*/
