#ifndef Payload_H
#define Payload_H

  #include <netinet/in.h>
  #include <stdlib.h>
  #include <stdbool.h>

  #ifndef CLIENT_PAR_MAXLENGTH
    #define CLIENT_PAR_MAXLENGTH 16
  #endif

  #ifndef ART_WORK_TITLE_LENGHT
    #define ART_WORK_TITLE_LENGHT 16
  #endif

  #ifndef ART_WORK_DESC_LENGHT
    #define ART_WORK_DESC_LENGHT 16
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

  typedef struct art_work {
    char title[ART_WORK_TITLE_LENGHT];
    char desc[ART_WORK_DESC_LENGHT];

    // TODO: Add other fields

  } art_work;

#endif
