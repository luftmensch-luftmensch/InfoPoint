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

// Header custom files

#include "utils/common/utils.h"           // Custom functions
#include "utils/common/welcome_message.h" // Welcome message


int main(){
  // Welcome message
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET , ascii_server_message);
  
}
