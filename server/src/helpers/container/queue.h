/*
  ╔═╗   ╦ ╦  ╔═╗  ╦ ╦  ╔═╗
  ║═╬╗  ║ ║  ║╣   ║ ║  ║╣ 
  ╚═╝╚  ╚═╝  ╚═╝  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/
	

#ifndef _QUEUE_H_
#define _QUEUE_H_

  #include <stdlib.h>
  #include <stdbool.h>

  /* =================================== Types ======================================= */

  typedef struct node {
    struct node* next;		/* Reference to the next node */
    void* data;			/* Content of the node */
  } node_t;

  typedef struct queue {
    node_t* head;		/* Reference to the head of the queue */
    node_t* tail;		/* Reference to the tail of the queue */
    size_t size;		/* Size of the queue */
  } queue_t;

  /* =================================== Function Prototyes ======================================= */

  /* Constructor of the queue */
  queue_t* init_queue();

  /* Destructor of the queue */
  void destroy_queue(queue_t*);

  /* Push a new node into the queue */
  bool enqueue(queue_t*, void*);

  /* Peek a node from the queue */
  void* dequeue(queue_t*);

  /* Retrieve the length of the queue */
  size_t retrieve_queue_size(const queue_t*);

  /* Check if the given queue is empty */
  bool is_empty(const queue_t*);

#endif
