/*
  ╔═╗  ╔╗╔  ╔╦╗  ╦═╗  ╦ ╦
  ║╣   ║║║   ║   ╠╦╝  ╚╦╝
  ╚═╝  ╝╚╝   ╩   ╩╚═   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _ENTRY_H_
#define _ENTRY_H_

  // An entry is the fundamental unit of a dictionary, containing a value to be stored and a key used to refer to it
  typedef struct entry {
    // In order to make as general as possible the entry we are going to use for both key & value a void pointer
    void* key;
    void* value;
  } entry;

  /*
   * Constructor for the entry
   * Unsing void* types allows to store any data type
  */
  struct entry init_entry(void*, unsigned long, void*, unsigned long);

  /* Destructor for the entry */
  void destroy_entry(struct entry*);

#endif
