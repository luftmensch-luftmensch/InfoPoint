/*
  ╔═╗   ╦ ╦  ╔═╗  ╦ ╦  ╔═╗
  ║═╬╗  ║ ║  ║╣   ║ ║  ║╣ 
  ╚═╝╚  ╚═╝  ╚═╝  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include "queue.h"
#include "linked_list.h"

void  push(struct queue*, void*, unsigned long);
void  pop(struct queue*);
void* peek(struct queue*);


struct queue init_queue(){
  struct queue new_queue;

  // Instantiate queue list member via ll constructor
  new_queue.list = init_ll();

  // Define member functions
  new_queue.push = push;
  new_queue.peek = peek;
  new_queue.pop  = pop;
  return new_queue;
}

void destroy_queue(struct queue* queue_to_destroy) { destroy_ll(&queue_to_destroy->list); }


void push(struct queue* q, void* data, unsigned long size) {
  // Use insert fun given from linked list with enforced parameters.
  q->list.insert(&q->list, q->list.lenght, data, size);
}
void pop(struct queue* q) {
  // Use remove fun given from linked list with enforced parameters.
  q->list.remove(&q->list, 0);
}

void* peek(struct queue* q) {
  // Use retrieve fun given from linked list with enforced parameters.
  return q->list.retrieve(&q->list, 0);
}
