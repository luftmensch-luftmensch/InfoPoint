/*
  ╔═╗  ╔╗╔  ╔╦╗  ╦═╗  ╦ ╦
  ║╣   ║║║   ║   ╠╦╝  ╚╦╝
  ╚═╝  ╝╚╝   ╩   ╩╚═   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )

*/

#include "entry.h"
#include <stdlib.h>
#include <string.h>


struct entry init_entry(void* key, unsigned long k_size, void* value, unsigned long v_size) {
  // Create a new entry instance
  struct entry entry;

  // Allocate space on the heap for the key and value.
  entry.key = malloc(k_size);
  entry.value = malloc(v_size);

  // Copy the data parameters into the new entry.
  memcpy(entry.key, key, k_size);
  memcpy(entry.value, value, v_size);

  return entry;
}

void destroy_entry(struct entry* entry) {
  // Safe guard for the key
  if(entry->key)
    free(entry->key);

  // Safe guard for the value
  if(entry->value)
    free(entry->value);

  free(entry);
}
