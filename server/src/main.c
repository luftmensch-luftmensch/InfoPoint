/*
  ╔═╗┌─┐┬─┐┬  ┬┌─┐┬─┐
  ╚═╗├┤ ├┬┘└┐┌┘├┤ ├┬┘
  ╚═╝└─┘┴└─ └┘ └─┘┴└─
  Autori:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

// Header file
#include <stdio.h>      // Input & Output 
#include <string.h>     // Manipolazione di array di caratteri (in C non offre un tipo stringa built-in!)
#include <stdlib.h>     // Standard Library ( Informazioni sulle funzioni di allocazione/deallocazione di memoria )

#include <fcntl.h>      // File control options

#include <sys/socket.h> // Internet Protocol family 
#include <sys/types.h>  // typedef symbols and structures
#include <netinet/in.h> // Internet Address family 

#include <arpa/inet.h>  // Definizione di operazioni Internet
#include <netdb.h>      // Operazioni network dabatase

#include <unistd.h>     // Implementation-specific functions (such as close())

#include <pthread.h>    // Contiene dichiarazioni di funzione e mapping per le interfacce di threading (definisce una serie di costanti utilizzate da tali funzioni)

// Personal Headers
#include "utils/common/utils.h"        // Custom functions
#include "utils/socket/server.h"    // Custom functions
#include "utils/common/welcome_message.h" // Welcome message


#define PORT 9000
#define SERVER_BACKLOG 1000 // Number of connections handled at once

// Abbreviation for structures used
typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;
int main(int argc, char* argv[]){

  unsigned int port = 0;
  if(argc > 2)
    { _msgfatal("server only accepts one argument, port number!\nRun again with none or exactly one parameter!"); exit(EXIT_FAILURE); }
  else if(argc == 2){
    //port = atoi(argv[1]);
    port = (uint) strtoul(argv[1], NULL, 10);
    if(!port)
      { _msgfatal("Bad port number (NaN): <%s>!", argv[1]); exit(EXIT_FAILURE); }
  }
  setup_signals();
  server* s = server_init(port);
  printf("%lu", s ->conn_count);
}
