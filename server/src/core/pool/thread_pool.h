/*
  ╔╦╗  ╦ ╦  ╦═╗  ╔═╗  ╔═╗  ╔╦╗      ╔═╗  ╔═╗  ╔═╗  ╦
   ║   ╠═╣  ╠╦╝  ║╣   ╠═╣   ║║      ╠═╝  ║ ║  ║ ║  ║
   ╩   ╩ ╩  ╩╚═  ╚═╝  ╩ ╩  ═╩╝      ╩    ╚═╝  ╚═╝  ╩═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

  #include <pthread.h>
  #include "../../helpers/container/queue.h"
  /* =================================== Types ======================================= */

  /** Generic data structure used to represent a job perfomend by a thread inside the thread pool */
  typedef struct task {
    void* (*func)(void*);   /* Function to be executed  */
    void* arg;          /* Argument of the function */
  } task_t;


  /**
    The ThreadPool object is used to create a provided number of threads awaiting work to be added to a queue.
    Work takes the form of a function with arguments wrapped in a Job, which is added as the data to the work queue.
  */
  typedef struct thread_pool_t {
    pthread_t* threads;		/* Array of threads spawned by the thread pool */
    size_t threads_alive;	/* N° of threads currently active */

    pthread_mutex_t lock;	/* Mutex of the thread pool */
    pthread_cond_t signal;	/* Conditional variable for the thread pool */
    queue_t* queue;		/* Queue containing all the tasks that has to be executed */

    bool active;		/* Control switch for the worker threads */
    bool on_shutdown;		/* Control switch for the worker threads in order to signal shutdown */
  } thread_pool;

  /* =================================== Function Prototyes [Job] ======================================= */

  /* Task initializer */
  task_t* init_task(void* (*)(void*), void*);


  /* =================================== Function Prototyes [Thread Pool] ======================================= */
  thread_pool* init_thread_pool(size_t);
  void destroy_thread_pool(thread_pool*);

  /* Submit a task in the thread pool queue */
  bool submit_task(thread_pool*, task_t*);

#endif
