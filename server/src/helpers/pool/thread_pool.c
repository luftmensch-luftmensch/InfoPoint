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
#include "../handler/signal_handler.h"
#include "../logging/logging.h"

#define _m(type, format, ...) _msgcategory(type, "THREAD_POOL", format __VA_OPT__(,) __VA_ARGS__)

void destroy_task(task_t* task_to_destroy);

/* Retrieve the number of core/processors of the machine */
static size_t retrieve_proc_num() { return sysconf(_SC_NPROCESSORS_ONLN); }

void* execute_task(void* arg) {
  thread_pool_t* pool = (thread_pool_t*) arg;
  task_t* task_to_execute;

  for(;;) {
    /* ==== [Start of critical section] ==== */
    pthread_mutex_lock(&(pool->lock));
    // wait for the condition: a non-empty queue
    /**
      Wait on condition variable, check for spurious wakeups.
      When returning from pthread_cond_wait(), we own the lock.
    */
    while(is_empty(pool->queue) && (!pool->active)) {
      pthread_cond_wait(&(pool->signal), &(pool->lock));
    }

    if (!pool->active)
      break;

    task_to_execute = (task_t*) dequeue(pool->queue);
    pthread_mutex_unlock(&(pool->lock));
    /* ==== [End of critical section] ==== */

    printf("Pulled task n° %p\n", task_to_execute->arg);
  }

  pool->threads_alive--;
  pthread_mutex_unlock(&(pool->lock));
  pthread_exit(NULL);
  return NULL;
}

thread_pool_t* init_thread_pool(size_t amount) {
  /**
     If 0 is passed as parameter we are going to define the
     number of threads based on the specifics of the machine
     on which the pool is currently running
  */
  if (amount == 0)
	amount = retrieve_proc_num();

  thread_pool_t* pool = malloc(sizeof(struct thread_pool));

  if (pool == NULL) {
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool!", __FILE_NAME__, __func__);
    return NULL;
  }

  /* Thread Pool field initialization */
  pool->threads_alive = amount;

  _m(_msginfo, "[%s] (%s) Initialized thread_pool", __FILE_NAME__, __func__);

  /* Thread Pool queue initialization */
  if ((pool->queue = init_queue()) == NULL) { /* On failure deallocate the space of the pool to avoid leaks */
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->queue!", __FILE_NAME__, __func__);
    free(pool);
    return NULL;
  }

  _m(_msginfo, "[%s] (%s) Initialized thread_pool->queue\n", __FILE_NAME__, __func__);

  /* Thread Pool threads initialization */
  if ((pool->threads = malloc(sizeof(pthread_t[amount]))) == NULL) { /* On failure deallocate the space of the pool & pool->queue to avoid leaks */
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->threads!\n", __FILE_NAME__, __func__);
    destroy_queue(pool->queue);
    free(pool);
    return NULL;
  }

  _m(_msginfo, "[%s] (%s) Initialized thread_pool->threads\n", __FILE_NAME__, __func__);

  for (size_t i = 0; i < amount; i++) {
    if (pthread_create(&pool->threads[i], NULL, execute_task, pool) != 0) {
      _m(_msgfatal, "[%s] (%s) Failed to spawn thread n° %zu! Cause: %s\n", __FILE_NAME__, __func__, i, strerror(errno));
      perror("pthread_create: ");
      exit(errno);
    }
  }

  _m(_msginfo, "[%s] (%s) Initialized thread_pool->thread->routine\n", __FILE_NAME__, __func__);

  /* Initialize thread_pool mutex & cond */
  pthread_mutex_init(&(pool->lock), NULL);
  _m(_msginfo, "[%s] (%s) Initialized thread_pool->lock", __FILE_NAME__, __func__);
  pthread_cond_init(&(pool->signal), NULL);
  _m(_msginfo, "[%s] (%s) Initialized thread_pool->signal", __FILE_NAME__, __func__);

  return pool;
}

void destroy_thread_pool(thread_pool_t* pool_to_destroy) {
  _m(_msginfo, "[%s] (%s) Destroying the thread_pool as requested", __FILE_NAME__, __func__);
  pool_to_destroy->active = false; /* Disable the active control switch */

  /* ==== Start of critical section ==== */
  pthread_mutex_lock(&(pool_to_destroy->lock));

  pthread_cond_broadcast(&(pool_to_destroy->signal));

  /* Wait to end signaling before joining */
  for (size_t i = 0; i < pool_to_destroy->threads_alive; i++)
    pthread_join(pool_to_destroy->threads[i], NULL);

  pthread_mutex_unlock(&(pool_to_destroy->lock));
  /* ==== End of critical section ==== */

  /* Finally deallocate space occupied by the threads */
  free(pool_to_destroy->threads);

  /* Deallocate the queue used by the threads */
  destroy_queue(pool_to_destroy->queue);

  /* Destroy the mutex & the condition variable as we don't need it */
  pthread_mutex_destroy(&(pool_to_destroy->lock));
  pthread_cond_destroy(&(pool_to_destroy->signal));

  /* Finally destroy the thread_pool itself */
  free(pool_to_destroy);
}

bool submit_task(thread_pool_t* pool, task_t* task) {
  /* ==== Start of critical section ==== */
  pthread_mutex_lock(&(pool->lock));

  bool status = enqueue(pool->queue, task);

  /* Inform the threads that some task was added to the queue */
  pthread_cond_signal(&(pool->signal));
  pthread_mutex_unlock(&(pool->lock));
  /* ==== End of critical section ==== */

  return status;
}

task_t* init_task(void* (*task_func)(void*), void* task_arg) {
  task_t* new_task = malloc(sizeof(struct task));
  if (new_task == NULL)
    return NULL;

  /* Task field initialization */
  new_task->func = task_func;
  new_task->arg = task_arg;

  return new_task;
}

void destroy_task(task_t* task_to_destroy) {
  free(task_to_destroy);
}


void await_thread_pool(thread_pool_t* pool) {
  pthread_mutex_lock(&(pool->lock));
  while(pool->queue->size) 
    pthread_cond_wait(&(pool->signal), &(pool->lock));
  pthread_mutex_unlock(&(pool->lock));
}
