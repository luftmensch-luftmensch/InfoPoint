/*
  ╔╦╗  ╦  ╔═╗  ╔╦╗  ╦  ╔═╗  ╔╗╔  ╔═╗  ╦═╗  ╦ ╦
   ║║  ║  ║     ║   ║  ║ ║  ║║║  ╠═╣  ╠╦╝  ╚╦╝
  ═╩╝  ╩  ╚═╝   ╩   ╩  ╚═╝  ╝╚╝  ╩ ╩  ╩╚═   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )

*/


#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

  #include "entry.h"
  #include "../trees/binary_seach_tree.h"
  #include "../list/linked_list.h"

  // A dict (dictionary) is a collection of entry stored in a bst.
  typedef struct dict {
    struct bst tree;
    struct linked_list keys;

    // Add new items to the dictionary -> the user need only specify the key, value, and their respective sizes.
    void (*insert)(struct dict*, void *, unsigned long, void*, unsigned long);

    // Find the value associated with a given key  in the dictionary. Returns its value if found or NULL otherwise
    void* (*search)(struct dict*, void*, unsigned long);

  } dict;

  /* Constructor for a dict. It needs a compare function (used under the hood by the bst) */
  struct dict init_dict(int (*compare)(void*, void*));

  /* Destructor for a dict */
  void destroy_dict(struct dict*);

  /* Keys comparator */
  int compare_keys(void*, void*);

  /*
   * Recursive algorithm to destroy the nodes in a dict
   * This func overrides the bst one
  */
  void recursive_destroy_dict(struct node*);

  /* Add item to the dict */
  void insert_dict(struct dict*, void*, unsigned long, void*, unsigned long);

  /* Find the value for a given key in the dict */
  void* search_dict(struct dict*, void*, unsigned long);

#endif
