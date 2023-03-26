/*
  ╔╗╔  ╔═╗  ╔╦╗  ╔═╗
  ║║║  ║ ║   ║║  ║╣ 
  ╝╚╝  ╚═╝  ═╩╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include "node.h"
#include <stdlib.h>


struct node init_node(void* data, unsigned long size){
  if (size < 1) {
    exit(EXIT_FAILURE);
  }

  struct node new_node;

  // Allocate space for the data
  new_node.data = malloc(size);

  memcpy(new_node.data, data, size);

  // Initialize the pointers of the node (next & prev)
  new_node.next = NULL;
  new_node.prev = NULL;
  return new_node;
}

void destroy_node(struct node* node_to_destroy){
  free(node_to_destroy->data);
  free(node_to_destroy);
}
