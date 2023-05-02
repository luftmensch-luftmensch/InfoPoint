/*
  ╔═╗  ╦    ╦  ╔═╗  ╔╗╔  ╔╦╗
  ║    ║    ║  ║╣   ║║║   ║ 
  ╚═╝  ╩═╝  ╩  ╚═╝  ╝╚╝   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_
  #include <stdlib.h>
  #include <netinet/in.h>


  typedef struct client {
    const char* name; // Client name, a 64 byte len string
    const char* addr; // Client ip address

    // Detaild about client connections
    ssize_t fd;           // Client fd
    struct sockaddr_in transport;
    
  } client;

#endif
