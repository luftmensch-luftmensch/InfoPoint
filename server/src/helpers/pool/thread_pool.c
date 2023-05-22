/*
  ╔╦╗  ╦ ╦  ╦═╗  ╔═╗  ╔═╗  ╔╦╗      ╔═╗  ╔═╗  ╔═╗  ╦  
   ║   ╠═╣  ╠╦╝  ║╣   ╠═╣   ║║      ╠═╝  ║ ║  ║ ║  ║  
   ╩   ╩ ╩  ╩╚═  ╚═╝  ╩ ╩  ═╩╝      ╩    ╚═╝  ╚═╝  ╩═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <sys/prctl.h>

#include "thread_pool.h"

#define _m(type, format, ...) _msgcategory(type, "THREAD_POOL", format, ##__VA_ARGS__)

static volatile int _keep_alive;
static volatile int _on_hold;

/* =================================== Internal Function Prototyes ======================================= */

/* ========================== Workers ============================ */

/* Helper function to initialize a worker in the thread pool */
static int init_worker(thread_pool* thpool_p, struct worker** thread_p, int id);

/* Routine passed to each worker */
static void* worker_routine(struct worker* thread_p);

/* Set the calling thread in a state of hold */
static void hold_worker(int sig_id);

/* Destructor for a single worker */
static void destroy_worker(struct worker* thread_p);

/* ========================== Queue ============================ */

/* Helper function used to initialize a job_queue */
static int   init_job_queue(job_queue* jobqueue_p);

/* Helper function used to clear a job_queue */
static void  clear_job_queue(job_queue* jobqueue_p);

/* Add a job to the job_queue */
static void  push_into_job_queue(job_queue* jobqueue_p, struct job* newjob_p);

/* Peek a job to the job_queue */
static struct job* pull_from_job_queue(job_queue* jobqueue_p);

/* Destructor of the job_queue */
static void  destroy_job_queue(job_queue* jobqueue_p);

/* ========================== Semaphore ============================ */

/* Helper function to initialize the semaphore (NB: Possible values -> 0 or 1) */
static void init_semaphore(struct semaphore*, int);

/* Helper function to reset the semaphore (set to 0) */
static void reset_semaphore(struct semaphore*);

/* Helper function to push the semaphore at least on a single thread */
static void push_sem_to_single(struct semaphore*);

/* Helper function to push the semaphore to all threads */
static void push_sem_to_all(struct semaphore*);

/* Wait on semaphore util its value=0 */
static void wait_on_semaphore(struct semaphore*);


struct thread_pool* init_thread_pool(int thread_n) {
  _on_hold   = 0;
  _keep_alive = 1;

  if (thread_n < 0){
    thread_n = 0;
  }

  /* Allocate mem for the newly thread_pool */
  thread_pool* pool = (struct thread_pool*) malloc(sizeof(struct thread_pool));
  if (pool == NULL){
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool!", __FILE__, __func__);
    return NULL;
  }

  /* Initialize thread_pool fields */
  pool->threads_alive   = 0;
  pool->threads_working = 0;

  /* Initialize thread_pool->queue  */
  if (init_job_queue(&pool->jobqueue) == -1){
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->queue!", __FILE__, __func__);
    free(pool);
    return NULL;
  }

  /* Allocate space for the threads */
  pool->threads = (struct worker**)malloc(thread_n * sizeof(struct worker *));
  if (pool->threads == NULL){
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread_pool->threads!", __FILE__, __func__);
    destroy_job_queue(&pool->jobqueue);
    free(pool);
    return NULL;
  }

  /* Initialize thread_pool mutex & cond */
  pthread_mutex_init(&(pool->lock), NULL);
  pthread_cond_init(&pool->cond, NULL);

  /* Thread initialization */
  for (int i = 0; i <thread_n; i++){
    init_worker(pool, &pool->threads[i], i);
  }

  /* Wait until all the threads are initialized */
  while (pool->threads_alive != thread_n) {}

  return pool;
}

int add_work_to_thread_pool(struct thread_pool* thpool_p, void (*function_p)(void*), void* arg_p) {
  job* new_job =(struct job*)malloc(sizeof(struct job));
  if (new_job==NULL){
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for a new job!", __FILE__, __func__);
    return -1;
  }

  /* Initialize fields for the new job*/
  new_job->function = function_p;
  new_job->arg      = arg_p;

  /* Finally push the job to the queue */
  push_into_job_queue(&thpool_p->jobqueue, new_job);

  return 0;
}

void await_thread_pool(thread_pool* pool) {
  /* Lock the mutex as request by pthread_cond_wait */
  pthread_mutex_lock(&pool->lock);

  while (pool->jobqueue.len || pool->threads_working) {
    pthread_cond_wait(&pool->cond, &pool->lock);
  }
  /* Unlock the mutex */
  pthread_mutex_unlock(&pool->lock);
}

void pause_thread_pool(struct thread_pool* pool) {
  for (int n = 0; n < pool->threads_alive; n++){
    pthread_kill(pool->threads[n]->thread, SIGUSR1);
  }
}

void resume_thread_pool(thread_pool* pool) {
  // TODO: Complete it
  (void)pool;

  _on_hold = 0;
}

void destroy_thread_pool(thread_pool* pool) {
  /* If NULL there is no need to destroy it */
  if (pool == NULL) return;

  volatile int total = pool->threads_alive;

  /* End each single thread routine */
  _keep_alive = 0;

  /* Define a timeout for every thread in idle */
  double timeout = 1.0, elapsed = 0.0;
  time_t started, ended;

  time (&started);

  while (elapsed < timeout && pool->threads_alive) {
    push_sem_to_all(pool->jobqueue.has_jobs);
    time (&ended);
    elapsed = difftime(ended,started);
  }

  /* Polling remaining threads (running) */
  while (pool->threads_alive) {
    push_sem_to_all(pool->jobqueue.has_jobs);
    sleep(1);
  }

  /* Clean up the job_queue */
  destroy_job_queue(&pool->jobqueue);

  /* Free threads */
  for (int i = 0; i < total; i++){
    destroy_worker(pool->threads[i]);
  }

  /* Free others fields */
  free(pool->threads);
  free(pool);
}


int currently_working_threads(thread_pool* pool){
  return pool->threads_working;
}


/* ============================ WORKERS ============================== */

static int init_worker(thread_pool* p, struct worker** w, int id) {

  *w = (struct worker*) malloc(sizeof(struct worker));
  if (*w == NULL){
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the thread!", __FILE__, __func__);
    return -1;
  }

  /* Initialize worker fields */
  (*w)->pool = p;
  (*w)->id   = id;

  if(pthread_create(&(*w)->thread, NULL,  (void* (*)(void *)) worker_routine, (*w)) != 0) {
    _m(_msgfatal, "[%s] (%s) Failed to create a new thread!", __FILE__, __func__);
    perror("pthread_create: ");
    exit(errno);
  }

  /*
    Mark the thread identified by thread as detachad. In this way
    when a detached thread terminates, its resources are automatically
    released back to the system without the need for another thread
    to join with the terminated thread
  */
  if(pthread_detach((*w)->thread) != 0) {
    _m(_msgfatal, "[%s] (%s) Failed to mark the thread <%d> as detachable!", __FILE__, __func__, (*w)->id);
    perror("pthread_detach: ");
    exit(errno);
  }
  return 0;
}


static void hold_worker(int sig) {
  (void) sig;

  _on_hold = 1;

  while(_on_hold) {
    sleep(1);
  }
}

static void* worker_routine(struct worker* w) {
  // Setup profiling (helps on debugging)
  char thread_name[16] = {0};
  snprintf(thread_name, 16, "thpool-%d", w->id);

  /* Thread manipulation with prctl (avoid _GNU_SOURCE flag & implicit declaration) */
  prctl(PR_SET_NAME, thread_name);

  /* Assert all threads have been created before starting serving */
  thread_pool* pool = w->pool;

  /* Signal handler registration */
  struct sigaction sig_a;
  sigemptyset(&sig_a.sa_mask);

  /*
    Many virtual machines, including Go VM, depend on signals using SA_ONSTACK.
    This flag allows a thread to define a new alternate signal stack.
    Many argue that SA_ONSTACK should be a default, but it's not the case
  */
  sig_a.sa_flags = 0; // SA_ONSTACK -> 0
  sig_a.sa_handler = hold_worker;
  if (sigaction(SIGUSR1, &sig_a, NULL) == -1) {
    _m(_msgfatal, "[%s] (%s) Failed to handle SIGUSR1 signal!", __FILE__, __func__);
  }

  /* Mark thread as active */
  pthread_mutex_lock(&pool->lock);
  pool->threads_alive += 1; // Increase the n° of threads alive accordingly
  pthread_mutex_unlock(&pool->lock);

  while(_keep_alive){

    /* Mark the thread as in work */
    wait_on_semaphore(pool->jobqueue.has_jobs);

    if (_keep_alive){

      pthread_mutex_lock(&pool->lock);
      pool->threads_working++; // Increase the n° of threads working accordingly
      pthread_mutex_unlock(&pool->lock);

      /* Read the job from the queue and execute it */

      void (*func_buff)(void*);
      void*  arg_buff;
      job* job_p = pull_from_job_queue(&pool->jobqueue);

      if (job_p) {
	func_buff = job_p->function;
	arg_buff  = job_p->arg;
	func_buff(arg_buff);
	free(job_p);
      }

      /* Once the job has terminated update the pool accordingly */
      pthread_mutex_lock(&pool->lock);
      pool->threads_working--;

      /* Check if there are no threads working left */
      if (!pool->threads_working) {
	pthread_cond_signal(&pool->cond);
      }
      pthread_mutex_unlock(&pool->lock);

    }
  }

  /* Update the pool accordingly once the thread is not more alive (decrease the counter) */
  pthread_mutex_lock(&pool->lock);
  pool->threads_alive --;
  pthread_mutex_unlock(&pool->lock);

  return NULL;
}


static void destroy_worker(worker* thread_p) {
  free(thread_p);
}

/* ============================ JOB QUEUE =========================== */

static int init_job_queue(job_queue* queue) {
  /* Initialize job_queue fields */
  queue->len = 0;
  queue->front = NULL;
  queue->rear  = NULL;

  queue->has_jobs = (struct semaphore*) malloc(sizeof(struct semaphore));
  if (queue->has_jobs == NULL){
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for the queue->has_jobs (semaphore)!", __FILE__, __func__);
    return -1;
  }

  pthread_mutex_init(&(queue->r_w_mutex), NULL);
  init_semaphore(queue->has_jobs, 0);

  return 0;
}

static void clear_job_queue(job_queue* queue) {
  while(queue->len){
    free(pull_from_job_queue(queue));
  }

  // "Reset" queue fields
  queue->front = NULL;
  queue->rear  = NULL;
  reset_semaphore(queue->has_jobs);
  queue->len = 0;
}


static void push_into_job_queue(job_queue* queue, struct job* new_job) {

  pthread_mutex_lock(&queue->r_w_mutex);
  new_job->prev = NULL;

  switch(queue->len) {
    case 0:  /* No jobs in queue */
      queue->front = new_job;
      queue->rear  = new_job;
      break;

    default: /* At least one job in the queue */
      queue->rear->prev = new_job;
      queue->rear = new_job;
  }

  // Increase the length accordingly
  queue->len++;

  push_sem_to_single(queue->has_jobs);
  pthread_mutex_unlock(&queue->r_w_mutex);
}


static struct job* pull_from_job_queue(job_queue* queue) {

  pthread_mutex_lock(&queue->r_w_mutex);
  job* job_p = queue->front;

  switch(queue->len){
  case 0:  /* No jobs in the queue */
    break;

  case 1:  /* There is only one job left in the queue */
    queue->front = NULL;
    queue->rear  = NULL;
    queue->len = 0;
    break;

  default: /* More then a single job in the queue */
    queue->front = job_p->prev;
    queue->len--;
    push_sem_to_single(queue->has_jobs);
  }

  pthread_mutex_unlock(&queue->r_w_mutex);
  return job_p;
}


static void destroy_job_queue(job_queue* to_destroy) {
  /* Return resources back to the system */
  clear_job_queue(to_destroy);
  free(to_destroy->has_jobs);
}


/* ======================== SEMAPHORE ========================= */

static void init_semaphore(semaphore* sem, int val) {
  if (val < 0 || val > 1) {
    _m(_msgfatal, "[%s] (%s) Failed to instantiate semaphore: The given value <%d> is not valid! (Accepted values are 0 or 1)", __FILE__, __func__, val);
    exit(1);
  }

  pthread_mutex_init(&(sem->mutex), NULL);
  pthread_cond_init(&(sem->cond), NULL);
  sem->v = val;
}


static void reset_semaphore(semaphore* sem) {
  init_semaphore(sem, 0);
}


static void push_sem_to_single(semaphore* sem) {
  pthread_mutex_lock(&sem->mutex);
  sem->v = 1;
  pthread_cond_signal(&sem->cond);
  pthread_mutex_unlock(&sem->mutex);
}


static void push_sem_to_all(semaphore* sem) {
  pthread_mutex_lock(&sem->mutex);
  sem->v = 1;
  pthread_cond_broadcast(&sem->cond);
  pthread_mutex_unlock(&sem->mutex);
}


static void wait_on_semaphore(semaphore* sem) {
  pthread_mutex_lock(&sem->mutex);
  while (sem->v != 1) {
    pthread_cond_wait(&sem->cond, &sem->mutex);
  }
  sem->v = 0;
  pthread_mutex_unlock(&sem->mutex);
}
