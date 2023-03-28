/*
  ╦    ╦  ╔╗╔  ╦╔═  ╔═╗  ╔╦╗      ╦    ╦  ╔═╗  ╔╦╗
  ║    ║  ║║║  ╠╩╗  ║╣    ║║      ║    ║  ╚═╗   ║ 
  ╩═╝  ╩  ╝╚╝  ╩ ╩  ╚═╝  ═╩╝      ╩═╝  ╩  ╚═╝   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/ 

#include "linked_list.h"

// Create a new node to add to the chain allocating space on the heap and calling the node constructor
struct node* create_node_ll(void*, unsigned long);

// Destroy the specified node by deallocating it's memory addr. Under the hood this fun call the node destructor fun
void destroy_node_ll(struct node*);


// Iterate the list from the begginning to the end
struct node* iterate_ll(struct linked_list*, int);

// Insert a new node into the linked list
void insert_ll(struct linked_list*, int, void*, unsigned long);

// Remove a given node from the list
void remove_node_ll(struct linked_list*, int);

// Access data in the list
void* retrieve_ll(struct linked_list*, int);

/*
 * The sort function is used to sort data in the list.
 * Note that this is a permanent change and items added after sorting will not themselves be sorted.
*/
void bubble_sort_ll(struct linked_list*, int (*compare)(void *, void *));

short binary_search_ll(struct linked_list*, void*, int (*compare)(void*, void*));


struct linked_list init_ll(){
  struct linked_list ll;

  // Initialization of linked list fields
  ll.head = NULL;
  ll.lenght = 0;

  // Initialization of linked list specific fun
  ll.insert = insert_ll;
  ll.remove = remove_node_ll;
  ll.retrieve = retrieve_ll;
  ll.sort = bubble_sort_ll;
  ll.search = binary_search_ll;
  
  return ll;
}

void destroy_ll(struct linked_list* ll) {
  for (int i = 0; i < ll->lenght; i++)
    ll->remove(ll, 0);
}

struct node* create_node_ll(void* data, unsigned long size) {
  struct node* new_node = (struct node*) malloc(sizeof(struct node));

  // Call the constructor for the new node
  *new_node = init_node(data, size);
  
  return new_node;
}

void destroy_node_ll(struct node* node_to_destroy) { destroy_node(node_to_destroy); }

struct node* iterate_ll(struct linked_list* ll, int index) {
  // Check if the specified index is valid!
  if (index < 0 || index >= ll->lenght) {
    return NULL;
  }
  
  struct node* cursor = ll->head;

  // Iterate until reaching the desired index
  for (int i = 0; i < index; i++) {
    cursor = cursor->next;
  }
  return cursor;
}

void insert_ll(struct linked_list* ll, int index, void* data, unsigned long size) {
  // New node creation
  struct node* new_node = create_node_ll(data, size);

  // Check if thew new_node should become the new head

  if (index == 0) {
    new_node->next = ll->head;
    ll->head = new_node;
  } else {
    // Find the node in the list in the position before the desired index
    struct node* cursor = iterate_ll(ll, index - 1);

    // Update the list accordingly
    new_node->next = cursor->next;
    cursor->next = new_node;
  }

  // Increment the list lenght
  ll->lenght++;
}

void remove_node_ll(struct linked_list* ll, int index) {
  // Check if the node to be removed is the current head
  if (index == 0) {
    // Retrieve the node to be removed
    struct node* to_remove = ll->head;

    if (to_remove) {
      // Update the head
      ll->head = to_remove->next;
      destroy_node_ll(to_remove);
    }
  } else {
    // Find the item in the list before the one that is going to be removed.
    struct node* cursor = iterate_ll(ll, index - 1);

    // Update the list accordingly
    struct node* to_remove = cursor->next;
    cursor->next = to_remove->next;

    destroy_node_ll(to_remove);
  }

  // Decrement the list lenght
  ll->lenght--;
}

void* retrieve_ll(struct linked_list* ll, int index) {
  // Find the desired node and return its data
  struct node* cursor = iterate_ll(ll, index);
  
  if(cursor)
    return cursor->data;
  else
    return NULL;
}

void bubble_sort_ll(struct linked_list* ll, int (*compare)(void *a, void *b)) {
  for (struct node* node_n = ll->retrieve(ll, 0); node_n ; node_n =node_n->next) {
    for (struct node* node_m = node_n->next; node_m ; node_m = node_m->next) {
      if (compare(node_n->data, node_m->data) > 0) {
	// Swap
	void* tmp = node_m->data;
	node_m->data = node_n->data;
	node_n->data = tmp;
      }
    }
  }
}


short binary_search_ll(struct linked_list* ll, void* q, int (*compare)(void* n, void* m)) {
  int pos = ll->lenght/2;
  int under_boundary = 0;
  int upper_boundary = ll->lenght;

  while(upper_boundary > under_boundary) {
    void* data = ll->retrieve(ll, pos);
    if (compare(data, q) == 1) {
      upper_boundary = pos;
      if (pos != (under_boundary + pos) / 2) {
	pos  = (under_boundary + pos) / 2;
      } else {
	break;
      }
    } else if (compare(data, q) == -1) {
      under_boundary = pos;

      if (pos != (upper_boundary + pos) / 2) {
	pos  = (upper_boundary + pos) / 2;
      } else {
	break;
      }
    } else {
      return 1;
    }

  }
  return 0;
}
