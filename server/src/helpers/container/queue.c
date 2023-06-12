/*
  ╔═╗   ╦ ╦  ╔═╗  ╦ ╦  ╔═╗
  ║═╬╗  ║ ║  ║╣   ║ ║  ║╣ 
  ╚═╝╚  ╚═╝  ╚═╝  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/
	

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

#include "../logging/logging.h"

#define _m(type, format, ...) _msgcategory(type, "QUEUE", format __VA_OPT__(,) __VA_ARGS__)

size_t retrieve_queue_size(const queue_t* q) { return q->size; }
bool is_empty(const queue_t* q) { return q->size == 0 ? true : false; }

queue_t* init_queue() {
  queue_t* new_queue = malloc(sizeof(struct queue));
	
  if (new_queue == NULL) {
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for a new job!", __FILE_NAME__, __func__);
    return NULL;
  }

  /* Queue field initialization */
  new_queue->size = 0;
  new_queue->head = new_queue->tail = NULL;
  return new_queue;
}

void destroy_queue(queue_t* queue_to_destroy) {
  while(queue_to_destroy->size) /* Free all nodes from the queue by pulling them */
    free(dequeue(queue_to_destroy));

  free(queue_to_destroy); /* Finally free the structure itself */
}


bool enqueue(queue_t* q, void* data) {
  node_t* new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    _m(_msgfatal, "[%s] (%s) Failed to allocate memory for a new job!", __FILE_NAME__, __func__);
    return false;
  }
  /* New Node field initialization */
  new_node->data = data;
  new_node->next = NULL;

  switch(q->size) {
    case 0:	/* No nodes in the queue */
      q->head = q->tail = new_node;
      break;
    default:	/* At least one node in the queue */
      q->tail->next = new_node;
      q->tail = new_node;
  }
  q->size++;

  return true;
}

void* dequeue(queue_t* q) {
  node_t* retrieved_node = q->head;
  switch(q->size) {
    case 0:	/* No nodes in the queue */
      break;
    case 1:	/* There is only a node left in the queue */
      q->head = q->tail = NULL;
      q->size = 0;
      break;
    default:	/* More then one node in the queue */
      q->head = q->head->next;
      q->size--;
  }

  return retrieved_node;
}


/*
int main() {
  queue_t* q = init_queue();

  enqueue(q, (void*) 1);
  enqueue(q, (void*) 2);
  enqueue(q, (void*) 3);
  enqueue(q, (void*) 4);
  enqueue(q, (void*) 5);



  printf("Before: %zu\n", q->size);

  while(!is_empty(q)) {
    node_t* n = dequeue(q);
    printf("%p\n", (int*) n->data);
    free(n);
  }
  
  printf("After: %zu\n", q->size);
  destroy_queue(q);
}
*/
