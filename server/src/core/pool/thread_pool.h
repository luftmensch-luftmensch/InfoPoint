/*
  ╔╦╗  ╦ ╦  ╦═╗  ╔═╗  ╔═╗  ╔╦╗      ╔═╗  ╔═╗  ╔═╗  ╦  
   ║   ╠═╣  ╠╦╝  ║╣   ╠═╣   ║║      ╠═╝  ║ ║  ║ ║  ║  
   ╩   ╩ ╩  ╩╚═  ╚═╝  ╩ ╩  ═╩╝      ╩    ╚═╝  ╚═╝  ╩═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

/*
  The ThreadPool object is used to create a provided number of threads awaiting work to be added to a queue.
  Work takes the form of a function with arguments wrapped in a ThreadJob, which is added as the data to the work queue.
*/

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

  #include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>

  #include "../../common/container/list/queue.h"
  #include "../../common/logging/logging.h"

  typedef struct thread_job {
    // Func to be executed
    void* (*job)(void*);

    // Argument passed to the fun
    void* arg;

  } thread_job;

  typedef struct thread_pool {
    int thread_n; // N° of threads in the thread_pool
    int active;   // Control switch for the thread pool

    struct queue queue; // Queue to store the scheduled work

    // Thread-safe pool operation using Mutex
    pthread_t* pool;
    pthread_mutex_t lock;
    pthread_cond_t signal;

    // Handler func to safely add tasks to the queue
    void (*add_task)(struct thread_pool*, struct thread_job);

  } thread_pool;


  /* Constructor of a thread pool */
  struct thread_pool init_thread_pool(int);


  /* Destructor of a thread pool */
  void destroy_thread_pool(thread_pool*);

  /* Constructor of a thread job */
  thread_job* init_thread_job(void* (*job) (void*), void*);

#endif
