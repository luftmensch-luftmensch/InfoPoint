/*
  ╔╗   ╦  ╔╗╔  ╔═╗  ╦═╗  ╦ ╦        ╔═╗  ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╦ ╦      ╔╦╗  ╦═╗  ╔═╗  ╔═╗
  ╠╩╗  ║  ║║║  ╠═╣  ╠╦╝  ╚╦╝        ╚═╗  ║╣   ╠═╣  ╠╦╝  ║    ╠═╣       ║   ╠╦╝  ║╣   ║╣ 
  ╚═╝  ╩  ╝╚╝  ╩ ╩  ╩╚═   ╩         ╚═╝  ╚═╝  ╩ ╩  ╩╚═  ╚═╝  ╩ ╩       ╩   ╩╚═  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

/*
 The BinarySearch tree struct is a collection of Nodes, each containing pointers to no more than two children.
 Children with data values less than the parent are stored to the left (previous), and those with values grater than the parent are stored to the right (next).
 Since the data type of the Nodes is unknown, users must specify their own comparison function for the tree in its constructor.
 Note that these functions should compare the stored data - not the Nodes themselves.
 Some generic comparison functions are provided for convenience.
*/

#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

  #include "../node/node.h"

  typedef struct bst {
    struct node* head;
    /*
     * The `compare` function must be specified by the user in order to define how to compare two nodes
     * 
     * To generalize it's accept two void pointers as arg and returns <1, -1, or 0>
    */
    int (*compare)(void*, void*);

    // Find a node in the tree, returning its data or NULL if not found.
    void* (*search)(struct bst*, void*);

    // Add a new node to the tree. Since memory allocation is handled by the node constructor, the size of this node's data must be specified.
    void (*insert)(struct bst*, void*, unsigned long);
  } bst;

  // Functions prototypes

  /* Constructor for the bst */
  struct bst init_bst(int(*compare)(void*, void*));

  /* Destructor for the bst */
  void destroy_bst(struct bst);

  /* Comparison helper function */
  int bst_str_compare(void*, void *);

  /* HELPERS FUNCTIONS */

  // Allocate space on the heap for a node and call the specific node constructor to instantiate it.
  struct node* create_node_bst(void*, unsigned long);

  // Remove a node by deallocating it's memory address. Under the hood it's an alias for the node destructor func.
  void destroy_node_bst(struct node*);

  /*
   * Recursive algorith used to traverse the brances of the given tree.
   *
   * It use the compare function (defined on the creation of the three) to determine the direction to use (left or right), returning the cursor once
   * there is no other position on which iterate.
   *
   * This function take a reference to the bst, the current position, the desired data, and an int pointer as arg (used as output param)
   * 
   * Possibile values for the int pointer are: 1 (if the desired data is > then returner node), -1 (if the desired data is < then returner node) or 0 (if are equal)
  */
  struct node* iterate_bst(struct bst*, struct node*, void*, int*);
  void recursive_destroy_bst(struct node*);

  /*
   * Uses the iterate func to test if a given node exists in the three.
   * If the node is found we are returing its data.
   * Otherwirse, NULL is returned
  */
  void* search_bst(struct bst*, void*);

  /* Add new node to the tree in a proper position */
  void insert_bst(struct bst*, void*, unsigned long);

#endif
