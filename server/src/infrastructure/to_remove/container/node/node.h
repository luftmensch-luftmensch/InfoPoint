/*
  ╔╗╔  ╔═╗  ╔╦╗  ╔═╗
  ║║║  ║ ║   ║║  ║╣ 
  ╝╚╝  ╚═╝  ═╩╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

/*
 The Node struct is the foundation for list objects, functioning like a single cell in the list.
 Nodes utilize void pointers to store data, in order to store any data type.
 
 Typically, nodes should not be manually instantiated.
 Usage is typically handled by the various list objects.
 
 In order to work, this requires the data to be allocated on the heap prior to being inserted into a node object.
 Typically, this is handled automatically when the node constructor is used;
 however, custom data types (those not included in the enumeration) need to be allocated manually and the data type Special should be used.
 
 In order to destroy a node, the node destructor is recommended as it will free both the stored data and the node itself automatically.
*/

#ifndef _NODE_H_
#define _NODE_H_

  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>

  // Nodes are used to store data of any type in a list.
  typedef struct node {
    /*
      To generalize the data insertable in the node,
      we are using a void point -> a casting is required for a proper access!
    */
    void* data;

    struct node* next; // Pointer to the next node in the chain
    struct node* prev; // Pointer to the previous node in the chain
  } node;

  /* Constructor of a node */
  struct node init_node(void*, unsigned long);

  /* Destructor of a node */
  void destroy_node(struct node*);

#endif
