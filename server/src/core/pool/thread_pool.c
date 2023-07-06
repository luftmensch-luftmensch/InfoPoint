/*
  ╔╦╗  ╦ ╦  ╦═╗  ╔═╗  ╔═╗  ╔╦╗      ╔═╗  ╔═╗  ╔═╗  ╦
   ║   ╠═╣  ╠╦╝  ║╣   ╠═╣   ║║      ╠═╝  ║ ║  ║ ║  ║
   ╩   ╩ ╩  ╩╚═  ╚═╝  ╩ ╩  ═╩╝      ╩    ╚═╝  ╚═╝  ╩═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "thread_pool.h"
#include "../message/message.h"
#include "../../helpers/handler/signal_handler.h"
#include "../../helpers/logging/logging.h"
#include "../payload/payload.h"

#define _m(type, format, ...) _msgcategory(type, "THREAD_POOL", format __VA_OPT__(,) __VA_ARGS__)

static char token[] = "token";
static char token_msg[] = "<>TOKEN:token<>\n";

static char initial_msg[]		= "<>STATUS:Server ready<>\n";
static char successful_response[]	= "<>RESPONSE:SUCCESS<>\n";
static char failed_response[]		= "<>RESPONSE:FAIL<>\n";
static char invalid_token[]		= "<>RESPONSE:Invalid token<>\n";
static char invalid_request[]		= "<>RESPONSE:Invalid request<>\n";
static char unauthorized_user[]		= "<>RESPONSE:Unauthorized user<>\n";

/* Retrieve the number of core/processors of the machine */
static size_t retrieve_proc_num() { return sysconf(_SC_NPROCESSORS_ONLN); }

/* Request handler used by the worker threads */
static void handle_request(request*, mongoc_client_t*, char*, char*, char*, ssize_t);

void* execute_task(void* arg);

thread_pool* init_thread_pool(size_t amount, char* username, char* password, char* host, char* database_name) {
  /**
     If 0 is passed as parameter we are going to define the
     number of threads based on the specifics of the machine
     on which the pool is currently running
  */
  if (amount == 0)
    amount = retrieve_proc_num();

  thread_pool* pool = malloc(sizeof(struct thread_pool_t));

  if (pool == NULL) {
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool!", __FILE_NAME__, __func__);
    return NULL;
  }

  /* Thread Pool field initialization */
  pool->active = true;
  pool->on_shutdown = false;

  pool->threads_alive = amount;

  /* Thread Pool queue initialization */
  _m(_msginfo, "[%s] (%s) Initializing thread_pool->queue", __FILE_NAME__, __func__);
  if ((pool->queue = init_queue()) == NULL) { /* On failure deallocate the space of the pool to avoid leaks */
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->queue!", __FILE_NAME__, __func__);
    free(pool);
    return NULL;
  }

  /* Thread Pool database handler initialization */
  if ((pool->handler = init_handler(username, password, host, database_name)) == NULL) { /* On failure deallocate the space of the pool to avoid leaks */
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->handler!", __FILE_NAME__, __func__);
    destroy_queue(pool->queue);
    free(pool);
    return NULL;
  }

  /* Thread Pool threads initialization */
  _m(_msginfo, "[%s] (%s) Initializing thread_pool->threads", __FILE_NAME__, __func__);
  if ((pool->threads = malloc(sizeof(pthread_t[amount]))) == NULL) { /* On failure deallocate the space of the pool to avoid leaks */
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->threads!", __FILE_NAME__, __func__);
    destroy_queue(pool->queue);
    free(pool);
    return NULL;
  }

  /* Thread Pool mutex & cond initialization */
  pthread_mutex_init(&(pool->lock), NULL);
  _m(_msginfo, "[%s] (%s) Initialized thread_pool->lock", __FILE_NAME__, __func__);

  pthread_cond_init(&(pool->signal), NULL);
  _m(_msginfo, "[%s] (%s) Initialized thread_pool->signal", __FILE_NAME__, __func__);

  /* Start worker thread */
  _m(_msginfo, "[%s] (%s) Initializing thread_pool->thread->routine", __FILE_NAME__, __func__);
  for (size_t i = 0; i < amount; i++) {
    if (pthread_create(&(pool->threads[i]), NULL, execute_task, (void*) pool) != 0) {
      _m(_msgfatal, "[%s] (%s) Failed to spawn thread n° %zu! Cause: %s\n", __FILE_NAME__, __func__, i, strerror(errno));
      perror("pthread_create: ");
      exit(errno);
    }
    _m(_msgevent, "[%s] (%s) Spawned thread n° %zu", __FILE_NAME__, __func__, i);
  }

  return pool;
}

void destroy_thread_pool(thread_pool* pool_to_destroy) {
  if (pool_to_destroy == NULL)
    return;

  _m(_msginfo, "[%s] (%s) Destroying the thread_pool as requested", __FILE_NAME__, __func__);
  pool_to_destroy->active = false;	/* Disable the active control switch */
  pool_to_destroy->on_shutdown = true;	/* Disable the active control switch */

  /* ==== [Start of critical section] ==== */
  pthread_mutex_lock(&(pool_to_destroy->lock));

  /* Wake up all worker threads */
    if (pthread_cond_broadcast(&(pool_to_destroy->signal)) != 0)
    _m(_msginfo, "[%s] (%s) Failed to signal all the threads as requested", __FILE_NAME__, __func__);

  if (pthread_mutex_unlock(&(pool_to_destroy->lock)) != 0)
    _m(_msgevent, "[%s] (%s) Failed to unlock pool->lock", __FILE_NAME__, __func__);

  _m(_msginfo, "[%s] (%s) Joining pool->threads as requested", __FILE_NAME__, __func__);

  /* Wait to end signaling before joining */
  for (size_t i = 0; i < pool_to_destroy->threads_alive; i++) {
    if(pthread_join(pool_to_destroy->threads[i], NULL) != 0) {
      _m(_msginfo, "[%s] (%s) Failed to join thread n° %zu as requested", __FILE_NAME__, __func__, i);
    }
  }

  _m(_msginfo, "[%s] (%s) Joined pool->threads as requested", __FILE_NAME__, __func__);
  /* ==== [End of critical section] ==== */

  /* Finally deallocate space occupied by the threads */
  free(pool_to_destroy->threads);

  /* Destroy the queue */
  destroy_queue(pool_to_destroy->queue);

  _m(_msginfo, "[%s] (%s) Destroying server->handler", __FILE_NAME__, __func__);
  destroy_handler(pool_to_destroy->handler);

  /* Destroy the mutex & the condition variable as we don't need it */
  pthread_mutex_destroy(&(pool_to_destroy->lock));
  pthread_cond_destroy(&(pool_to_destroy->signal));

  /* Finally destroy the thread_pool itself */
  free(pool_to_destroy);
}

bool submit_task(thread_pool* pool, void* data) {
  if ((pool == NULL) || (data == NULL))
    return false;

  /* ==== [Start of critical section] ==== */
  if(pthread_mutex_lock(&(pool->lock)) != 0)
    return false;

  bool status = enqueue(pool->queue, data);

  /* Inform the threads that some task was added to the queue */
  if (pthread_cond_signal(&(pool->signal)) != 0)
    return false;

  if (pthread_mutex_unlock(&(pool->lock)) != 0)
    return false;

  /* ==== [End of critical section] ==== */

  return status;
}

void* execute_task(void* arg) {
  thread_pool* pool = (thread_pool*) arg;

  // Node retrieved from the pool->queue used to take the socket file descriptor used to communicate
  node_t* node;

  // Socket File Descriptor - Value retrieved from the node
  ssize_t fd;

  char buffer[256];
  ssize_t bytes = 0;

  memset(buffer, 0, sizeof(buffer));

  for(;;) {
    /* Lock must be taken to wait on conditional variable */

    /* ==== [Start of critical section] ==== */
    pthread_mutex_lock(&(pool->lock));

    /**
       Wait on condition variable, check for spurious wakeups.
       When returning from pthread_cond_wait(), we own the lock.
    */
    while((is_empty(pool->queue)) && (!pool->on_shutdown))
      pthread_cond_wait(&(pool->signal), &(pool->lock));

    if (!pool->active)
      break;

    node = dequeue(pool->queue);
    pthread_mutex_unlock(&(pool->lock));
    /* ==== [End of critical section] ==== */

    /* Retrieve the socket fd from the node */
    fd = (ssize_t) node->data;
    /* And destroy the no more needed node to avoid leaks */
    free(node);
    msg_send(fd, initial_msg, sizeof(initial_msg), 0);

    bool read_again = true;
    bytes = msg_recv(fd, buffer, sizeof(buffer), 0, &read_again);

    if (bytes != 0) { 		/* Handle request only if something was received */
      request* r = parse_data(buffer, "<>", ":");

      mongoc_client_t* client = mongoc_client_pool_pop(pool->handler->instance.pool);
      handle_request(r, client, pool->handler->settings.name, pool->handler->settings.art_work_collection, pool->handler->settings.user_collection, fd);
      mongoc_client_pool_push(pool->handler->instance.pool, client);

      destroy_request(r);
    }
  }

  pthread_mutex_unlock(&(pool->lock));
  pthread_exit(NULL);
  return NULL;
}

static void handle_request(request* r, mongoc_client_t* client, char* db_name, char* art_work_collection, char* user_collection, ssize_t fd) {
  if ((r == NULL) || (client == NULL)) {
    _m(_msginfo, "[%s] (%s) Invalid request!", __FILE_NAME__, __func__);
    return;
  }

  printf("Request: <%s> <%s> <%s>\n", r->request_type, r->credential_username, r->credential_password);


  /* Parse the token received in order to remove any new line \n */
  r->token[strcspn(r->token, "\n")] = '\0';


  // <>REQUEST:POPULATE<>USERNAME:u<>PASSWORD:p<>TOKEN:i
  if (strcmp(r->request_type, "POPULATE") == 0) {
    populate_collection(client, db_name, art_work_collection);
    msg_send(fd, successful_response, sizeof(successful_response), 0);
  }


  if ((strcmp(r->request_type, "REGISTRATION") != 0) && (strcmp(r->token, token) != 0)) { /* If the token mismatched inform the user of the invalid token setted */
    _m(_msgevent, "[%s] (%s) Client on socket n° <%zu> made a request with a wrong token value <%s>!", __FILE_NAME__, __func__, fd, token);
    msg_send(fd, invalid_token, sizeof(invalid_token), 0);
    return;
  }

  /*
    Request type comparison for the type of task to do
    Unfortunately we cannot use a switch statement for this task,
    but a series of if/else if/else statement (more verbose, but certainly effective)
    is good enought
  */

  /* Before making any specific operation check for common operation between valid requests (RETIREVE, LOGIN, DELETE) */
  if ((strcmp(r->request_type, "RETRIEVE") == 0) ||
      (strcmp(r->request_type, "LOGIN") == 0)    ||
      (strcmp(r->request_type, "DELETE") == 0)) {
    _m(_msgevent, "[%s] (%s) Client on socket n° <%zu> is asking for a valid request [%s]", __FILE_NAME__, __func__, fd, r->request_type);

    /* Validate client credentials */
    bson_t* filter = BCON_NEW("name", BCON_UTF8(r->credential_username), "password", BCON_UTF8(r->credential_password));
    bson_t* opts = BCON_NEW("limit", BCON_INT64(1));

    bool status = is_present(client, filter, opts, db_name, user_collection);

    /* Don't forget to free the filter & the options used to avoid annoying leaks */
    bson_free(filter);
    bson_free(opts);

    /* If the user is not authenticate return, otherwise continue */
    if (status) {
      _m(_msginfo, "[%s] (%s) The user is correctly authenticated!", __FILE_NAME__, __func__);
    } else {
      msg_send(fd, unauthorized_user, sizeof(unauthorized_user), 0);
      return;
    }
  } else if (strcmp(r->request_type, "REGISTRATION") == 0) { /* Special operation for registration */
    bson_oid_t oid;
    bson_oid_init(&oid, NULL);
    bson_t* document = BCON_NEW("_id", BCON_OID(&oid),
				"name", BCON_UTF8(r->credential_username),
				"password", BCON_UTF8(r->credential_password));

    bool status = insert_single(client, document, db_name, user_collection);
    bson_free(document);

    if (status) {
      _m(_msginfo, "[%s] (%s) The user is correctly inserted! Informing the user...", __FILE_NAME__, __func__);
      msg_send(fd, token_msg, sizeof(token_msg), 0);
      msg_send(fd, successful_response, sizeof(successful_response), 0);
    } else {
      msg_send(fd, failed_response, sizeof(failed_response), 0);
    }

    /* Nothing to do here, so return */
    return;

  } else {
    _m(_msgevent, "[%s] (%s) Client on socket n° <%zu> is asking for an unknown request!", __FILE_NAME__, __func__, fd);
    /* Inform the user for the wrong request received */
    msg_send(fd, invalid_request, sizeof(invalid_request), 0);
    return;
  }

  /* Specific operation for LOGIN request */
  // <>REQUEST:LOGIN<>USERNAME:u<>PASSWORD:p<>TOKEN:i
  if (strcmp(r->request_type, "LOGIN") == 0) {
    msg_send(fd, successful_response, sizeof(successful_response), 0);
  }

  // <>REQUEST:DELETE<>USERNAME:u<>PASSWORD:p<>TOKEN:i
  if (strcmp(r->request_type, "DELETE") == 0) {
    bson_t* document = BCON_NEW("name", BCON_UTF8(r->credential_username), "password", BCON_UTF8(r->credential_password));
    bool status = delete_single(client, document, db_name, user_collection);
    bson_free(document);

    if (status) {
      _m(_msginfo, "[%s] (%s) The user is correctly removed! Informing the user...", __FILE_NAME__, __func__);
      msg_send(fd, successful_response, sizeof(successful_response), 0);
    } else {
      msg_send(fd, failed_response, sizeof(failed_response), 0);
    }

  }

  // <>REQUEST:RETRIEVE<>USERNAME:u<>PASSWORD:p<>TOKEN:i
  if (strcmp(r->request_type, "RETRIEVE") == 0) {
    retrieve_art_works(client, db_name, art_work_collection, fd);
    msg_send(fd, successful_response, sizeof(successful_response), 0);
  }


}
