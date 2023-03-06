#ifndef Client_H
#define Client_H

  #include <netinet/in.h>
  #include <stdlib.h>
  #include <stdbool.h>

  #ifndef CLIENT_PAR_MAXLENGTH
    #define CLIENT_PAR_MAXLENGTH 16
  #endif

  enum client_type { STUDENT, EXPERT };

  typedef struct client {
    // Attributes of the client
    char name[CLIENT_PAR_MAXLENGTH + 1];
    char password[CLIENT_PAR_MAXLENGTH + 1];
    char email;
    enum client_type type;
    char confirmation_code;
    bool confirmed;

    // Details about the client
    ssize_t socket;
    struct sockaddr_in transport;

  } client;

#endif
