/*
  ╔╦╗  ╦  ╔═╗  ╔╦╗  ╦  ╔═╗  ╔╗╔  ╔═╗  ╦═╗  ╦ ╦
   ║║  ║  ║     ║   ║  ║ ║  ║║║  ╠═╣  ╠╦╝  ╚╦╝
  ═╩╝  ╩  ╚═╝   ╩   ╩  ╚═╝  ╝╚╝  ╩ ╩  ╩╚═   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )

*/

#include "dictionary.h"
#include "entry.h"
#include <string.h>
#include <type_traits>

struct dict init_dict(int (*compare)(void* entry_one, void* entry_two)) {
  struct dict d;

  /* Dict field and member function initialization */
  d.tree = init_bst(compare);
  d.keys = init_ll();
  d.insert = insert_dict;
  d.search = search_dict;

  return d;
}

void destroy_dict(struct dict* dict) {
  destroy_ll(&dict->keys);
  recursive_destroy_dict(dict->tree.head);
}

void recursive_destroy_dict(struct node* node) {
  if (node->prev) {
    recursive_destroy_dict(node->prev);
  }
  if (node->next) {
    recursive_destroy_dict(node->next);
  }

  destroy_entry((struct entry*) node->data);
  free(node->data);
  free(node);
}

void* search_dict(struct dict* d, void* key, unsigned long k_size) {
  int support_k = 0;

  struct entry en = init_entry(key, k_size, &support_k, sizeof(support_k));

  // Use the specific bst function to find the desired element.
  void* res = d->tree.search(&d->tree, &en);

  if (res) {
    return ((struct entry*) res)->value;
  }  else {
    return NULL;
  }
}

void insert_dict(struct dict* dict, void* key, unsigned long k_size, void* value, unsigned long v_size) {
  // Create a new entry to add to the dict
  struct entry new_entry = init_entry(key, k_size, value, v_size);

  // Insert the new entry in the dict
  dict->tree.insert(&dict->tree, &new_entry, sizeof(new_entry));
  dict->keys.insert(&dict->keys, dict->keys.lenght, key, k_size);
}

int compare_keys(void* entry_one, void* entry_two) {
  if (strcmp( // Cast both to char*
	     (char *)(((struct entry*)entry_one)->key),
	     (char *)(((struct entry*)entry_two)->key)) > 0
      ) {
    return 1; 
  } else if (strcmp( // Cast both to char*
	     (char *)(((struct entry*)entry_one)->key),
	     (char *)(((struct entry*)entry_two)->key)) < 0
	     ) {
    return -1; 
  } else {
    return 0;
  }
}
