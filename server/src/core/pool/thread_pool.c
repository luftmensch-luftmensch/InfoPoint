/*
  ╔╦╗  ╦ ╦  ╦═╗  ╔═╗  ╔═╗  ╔╦╗      ╔═╗  ╔═╗  ╔═╗  ╦  
   ║   ╠═╣  ╠╦╝  ║╣   ╠═╣   ║║      ╠═╝  ║ ║  ║ ║  ║  
   ╩   ╩ ╩  ╩╚═  ╚═╝  ╩ ╩  ═╩╝      ╩    ╚═╝  ╚═╝  ╩═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include "pthread.h"
#include <pthread.h>

#include "thread_pool.h"

#define _m(type, format, ...) _msgcategory(type, "THREAD_POOL", format, ##__VA_ARGS__)



// Private memmber prototypes

/*
 * The do_work function is required as the argument of pthread_create in order to
 * create each thread in the loop.
 * It allows each thread to await a thread_job object and execute its content
 * In this way we are getting a dynamic pool -> this allows us to pass any fun as a job
*/
void* do_work(void*);

/* Add task to the queue in a thread-safe way */
void add_task(struct thread_pool*, struct thread_job);

struct thread_pool init_thread_pool(int thread_n) {
  _m(_msgevent, "Initialization of thread_pool as requested");
  // TODO: Handle case thread_n < 0
  struct thread_pool pool;

  // Thread pool field setup
  pool.thread_n = thread_n;
  pool.active = 1;

  _m(_msgevent, "Initialization of thread_pool->queue as requested");
  pool.queue = init_queue();

  // Thread mutex initialization
  _m(_msgevent, "Initialization of thread_pool->mutex as requested");

  pool.lock   = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
  pool.signal = (pthread_cond_t)  PTHREAD_COND_INITIALIZER;

  // Mutex locking in order to create thread_pool
  pthread_mutex_lock(&pool.lock);
  pool.pool = malloc(sizeof(pthread_t[thread_n]));

  for (int i = 0; i < thread_n; i++){
    if(pthread_create(&pool.pool[i], NULL, do_work, &pool) != 0) {
      _m(_msgfatal, "Could not create a new thread!");
      perror("pthread_create: ");
      exit(errno);
    }
  }

  // Unlock Mutex
  pthread_mutex_unlock(&pool.lock);

  pool.add_task = add_task;

  return pool;
}

void destroy_thread_pool(struct thread_pool* pool) {
  _m(_msginfo, "Shutting down thread_pool as requested");

  pool->active = 0;

  // Unblock all threads with signal
  for (int i = 0; i < pool->thread_n; i++) {
    if (pthread_cond_signal(&pool->signal) != 0) {
      _m(_msgfatal, "Failed to broadcast msg to threads");
      perror("pthread_cond_broadcast: ");
      exit(errno);
    }
  }

  // Wait for the thread to exit gracefully
  for (int i = 0; i < pool->thread_n; i++) {
    if (pthread_join(pool->pool[i], NULL) != 0) { // We are using NULL because we don't need a output param
      _m(_msgfatal, "Failed to join thread <%d>", i);
      perror("pthread_join: ");
      exit(errno);
    }
  }
  free(pool->pool);
  destroy_queue(&pool->queue);
}

void* do_work(void* arg) {
  struct thread_pool* pool = (struct thread_pool*) arg;
  while(pool->active == 1) {
    // Lock the queue in order to avoid undefined behaviour
    pthread_mutex_lock(&pool->lock);
    pthread_cond_wait(&pool->signal, &pool->lock);

    // Get job from the queue
    struct thread_job job = *(struct thread_job*)pool->queue.peek(&pool->queue);

    pool->queue.pop(&pool->queue);
    // Now we can unlock the queue in order to make available for other jobs
    pthread_mutex_unlock(&pool->lock);

    // Execute the job
    if (job.job)
      job.job(job.arg);
  }
  return NULL;
}

void add_task(struct thread_pool* pool, struct thread_job job) {
  // Lock the queue in order to avoid undefined behaviour (ie multiple threads accessing in the same time)
  pthread_mutex_lock(&pool->lock);
  // Push the new task to the queue
  pool->queue.push(&pool->queue, &job, sizeof(job));

  pthread_cond_signal(&pool->signal);

  // Now we can unlock the queue in order to make available for other threads
  pthread_mutex_unlock(&pool->lock);
}
