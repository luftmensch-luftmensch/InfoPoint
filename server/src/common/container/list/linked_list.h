/*
  ╦    ╦  ╔╗╔  ╦╔═  ╔═╗  ╔╦╗      ╦    ╦  ╔═╗  ╔╦╗
  ║    ║  ║║║  ╠╩╗  ║╣    ║║      ║    ║  ╚═╗   ║ 
  ╩═╝  ╩  ╝╚╝  ╩ ╩  ╚═╝  ═╩╝      ╩═╝  ╩  ╚═╝   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/ 

/*
 The LinkedList struct is a collection of Nodes, each pointing to the next one in the chain.
 This is a dynamic implementation of a linked list - it does not enforce ubiquitous data types and can be resized at any point.
 
 The object handles the creation and destruction of nodes automatically, allowing the user to simply insert the desired data.
 In order to provide this functionality, node data takes the form of void pointers, so it must be casted appropriately upon access.
 
 The constructor and destructor should be used to create and destroy instances of the LinkedList struct.
 
 Note that a reference to the LinkedList instance must be passed to the member functions.
 This is similar to passing "self" to class member functions in Python.
*/

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

  #include <stdlib.h>
  #include <stdio.h>

  #include "../node/node.h"

  // LinkedLists are used to move between and manipulate related nodes in an organized fashion.
  typedef struct linked_list {
    struct node* head; // The had points to the first node in the chain
    int lenght; // The lenght is used to indicate the number of nodes in the chain

    // Linked list functions

    /* Add new node to a specific linked_list in a specific position */
    void (*insert)(struct linked_list*, int, void*, unsigned long);

    /* Remove a specific item from the chain */
    void (*remove)(struct linked_list*, int);

    // Access to data in the chain
    void* (*retrieve)(struct linked_list*, int);

    // Sort & Search
    void (*sort)(struct linked_list*, int(*compare)(void*, void*));

    // Binary Search (the linked list must be sorted).
    short (*search)(struct linked_list*, void*, int(*compare)(void*, void*));

  } linked_list;

  // Function prototypes

  /* Constructor of a list */
  struct linked_list init_ll();

  /* Destructor of a list */
  void destroy_ll(struct linked_list*);

#endif
