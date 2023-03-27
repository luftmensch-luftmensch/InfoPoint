/*
  ╔═╗   ╦ ╦  ╔═╗  ╦ ╦  ╔═╗
  ║═╬╗  ║ ║  ║╣   ║ ║  ║╣ 
  ╚═╝╚  ╚═╝  ╚═╝  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

  #include "linked_list.h"

  // Queue are used to acces a linked list in a controlled manner
  typedef struct queue {
    // Ref to the embedded linked list
    struct linked_list list;

    /* PUBLIC MEMBER METHODS */

    // Add a node to the end of the chain.
    void (*push)(struct queue*, void *data, unsigned long size);

    // Retrieve data from the front of the list.
    void* (*peek)(struct queue*);

    // Remove first item in the list.
    void (*pop)(struct queue*);
  } queue;

  // Function prototypes

  /* Constructor of a queue */
  struct queue init_queue();

  /* Destructor of a queue */
  void destroy_queue(struct queue*);

#endif
