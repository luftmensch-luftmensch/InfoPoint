/*
  ╔╗   ╦  ╔╗╔  ╔═╗  ╦═╗  ╦ ╦        ╔═╗  ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╦ ╦      ╔╦╗  ╦═╗  ╔═╗  ╔═╗
  ╠╩╗  ║  ║║║  ╠═╣  ╠╦╝  ╚╦╝        ╚═╗  ║╣   ╠═╣  ╠╦╝  ║    ╠═╣       ║   ╠╦╝  ║╣   ║╣ 
  ╚═╝  ╩  ╝╚╝  ╩ ╩  ╩╚═   ╩         ╚═╝  ╚═╝  ╩ ╩  ╩╚═  ╚═╝  ╩ ╩       ╩   ╩╚═  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "binary_seach_tree.h"


struct bst init_bst(int(*compare)(void* d_1, void* d_2)) {
  struct bst tree;

  // Setup tree field
  tree.head = NULL;

  // Setup tree member functions
  tree.compare = compare;
  tree.search = search_bst;
  tree.insert = insert_bst;
  
  return tree;
}

void destroy_bst(struct bst tree) { recursive_destroy_bst(tree.head); }

struct node* create_node_bst(void* data, unsigned long size) {
  // Space allocation for the node
  struct node* node = (struct node*) malloc(sizeof(struct node));

  // Call the specific node constructor
  *node = init_node(data, size);
  return node;
}

void destroy_node_bst(struct node* node_to_destroy){ destroy_node(node_to_destroy); }

struct node* iterate_bst(struct bst* tree, struct node* cursor, void* data, int* direction) {
  // Comparision between the desired node and cursor data
  if (tree->compare(cursor->data, data) == 1) {
    // Check if there is another node in the chain to test
    if (cursor->next) {
      return iterate_bst(tree, cursor->next, data, direction);
    } else {
      // Set the direction accordingly to reflect the nex pos (moving to right)
      *direction = 1;
      return cursor;
    }
  } else if (tree->compare(cursor->data, data) == -1) {
    // Check if there is another node in the chain to test
    if (cursor->prev) {
      return iterate_bst(tree, cursor->prev, data, direction);
    } else {
      // Set the direction accordingly to reflect the nex pos (moving to left)
      *direction = -1;
      return cursor;
    }
  } else { // Two values are equal
    
    *direction = 0;
    return cursor;
  }
}

void recursive_destroy_bst(struct node* node) {
  // Safe guard (left)
  if (node->prev)
    recursive_destroy_bst(node->prev);

  // Safe guard (right)
  if (node->next)
    recursive_destroy_bst(node->next);

  destroy_node_bst(node);
}

void* search_bst(struct bst* tree, void* data) {
  // Set the direction pointer
  int direction = 0;

  struct node* cursor = iterate_bst(tree, tree->head, data, &direction);

  // Test if the found node is the desired node or an adiacent
  if (direction == 0) {
    return cursor->data;
  } else {
    return NULL;
  }
}

void insert_bst(struct bst* tree, void* data, unsigned long size) {
  // Check if we are on the first node in the tree
  if (!tree->head) {
    tree->head = create_node_bst(data, size);
  } else {
    // Set the direction pointer
    int direction = 0;

    // Find the desired position
    struct node* cursor = iterate_bst(tree, tree->head, data, &direction);

    // Check the direction for the new node (left || right)
    if (direction == 1) {
      cursor->next = create_node_bst(data, size);
    } else if (direction == -1) { 
      cursor->prev = create_node_bst(data, size);
    }

    // Duplicate nodes are not added!
  }
}

int bst_str_compare(void* data_one, void * data_two) {
  int status = strcmp(data_one, data_two);
  if (status > 0) {
    return 1;
  } else if (status < 0) {
    return -1;
  } else {
    return 0;
  }
}
