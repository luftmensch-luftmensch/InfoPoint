/*
  ╔╦╗  ╦ ╦  ╦═╗  ╔═╗  ╔═╗  ╔╦╗      ╔═╗  ╔═╗  ╔═╗  ╦  
   ║   ╠═╣  ╠╦╝  ║╣   ╠═╣   ║║      ╠═╝  ║ ║  ║ ║  ║  
   ╩   ╩ ╩  ╩╚═  ╚═╝  ╩ ╩  ═╩╝      ╩    ╚═╝  ╚═╝  ╩═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

/*
  The ThreadPool object is used to create a provided number of threads awaiting work to be added to a queue.
  Work takes the form of a function with arguments wrapped in a Job, which is added as the data to the work queue.
*/

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

  /*
   * Enabling this macro allow us to made available the functionality from the 2008 edition of the POSIX standard (IEEE Standard 1003.1-2008)
   * More reference at https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
  */
  #ifndef _POSIX_C_SOURCE
    #define _POSIX_C_SOURCE 200809L
  #endif

  #include <pthread.h>
  #include "../logging/logging.h"

  /* =================================== TYPES ======================================= */


  /* =================================== SEMAPHORE ======================================= */
  typedef struct semaphore {
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int v;
  } semaphore;


  /* =================================== JOB ======================================= */
  typedef struct job {
    struct job*  prev;             // Ref to previous job
    void   (*function)(void* arg); // Function executed by the job
    void*  arg;                    // Argument passed to the function
  } job;


  /* =================================== JOB QUEUE ======================================= */
  typedef struct job_queue {
    pthread_mutex_t r_w_mutex; // Mutex used for secure R/W access of the queue
    job* front;                // Ref to the front of queue
    job* rear;                 // Ref to the rear of queue
    semaphore* has_jobs;       // Semaphore used to get info about remaining jobs in the queue
    int   len;                 // N° of jobs remaining
  } job_queue;


  /* =================================== WORKER ======================================= */
  typedef struct worker {
    int       id;             // "Friendly" id of the worker
    pthread_t thread;         // Pointer to the actual thread
    struct thread_pool* pool; // Direct access to the thread_pool
  } worker;


  /* =================================== THREAD POOL ======================================= */
  typedef struct thread_pool {
    worker**   threads;           // Access to the workers
    volatile int threads_alive;   // N° of threads currently alive
    volatile int threads_working; // N° of threads currently working
    pthread_mutex_t lock;         // Mutex of the thread_pool
    pthread_cond_t  cond;         // Condition signal of the thread_pool
    job_queue  jobqueue;          // Queue to store the scheduled task
  } thread_pool;


  /* =================================== Function Prototyes ======================================= */

  /**
   * Initializes a threadpool with a given number of threads.
   * This function will not return until all
   * threads have initialized successfully.
  */
  struct thread_pool* init_thread_pool(int);

  /** Takes an action and its argument and adds it to the threadpool's job queue. */
  int add_work_to_thread_pool(struct thread_pool*, void (*function_p)(void*), void* arg_p);


  /**
   * Wait for all jobs to finish (both queued and currently running)
   *
   * Under the hood it uses smart polling is used in wait.
   * The polling is initially 0 - meaning that there is virtually no polling at all.
   * If after 1 seconds the threads haven't finished, the polling interval starts growing
   * until it reaches max_secs seconds. Then it jumps down to a maximum polling
   * interval assuming that heavy processing is being used in the threadpool.
   *
  */
  void await_thread_pool(struct thread_pool*);

  /**
   * Pauses all the threads immediately (no matter what if they are in idle or running).
   * The threads return to their previous state once the resume_thread_pool is called
   *
   * In the meantime, it's possible to add new threads
  */
  void pause_thread_pool(struct thread_pool*);

  /** Resume all the threads if they are paused */
  void resume_thread_pool(struct thread_pool*);

  /**
   * Destructor of the thread_pool
   *
   * Waits for the currently active threads to finish and then
   * free the memory used by the thread_pool
  */
  void destroy_thread_pool(struct thread_pool*);

  /** N° of currently threads active (not in idle) */
  int currently_working_threads(struct thread_pool*);

#endif
