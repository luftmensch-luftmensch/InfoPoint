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
#include "utils/common/handlers.h"        // Custom functions
#include "utils/common/socket_utils.h"    // Custom functions
#include "utils/common/welcome_message.h" // Welcome message


#define PORT 9000
#define SERVER_BACKLOG 1000 // Number of connections handled at once

// Abbreviation for structures used
typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int main(){
  // Welcome message
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET , ascii_server_message);

  int serverSocket, clientSocket, addressLen;

  SA_IN serverAddr, clientAddr;

  /**
     Socket creation. Parameters:
     1. INTERNET DOMAIN;
     2. SOCKET STREAM;
     3. TYPE OF PROTOCOL TO USE.
  */
  check((serverSocket = socket(AF_INET, SOCK_STREAM, 0)), "[-]Errore nella creazione della socket");
  logging("[+] Server socket inizializzata correttamente");
  
  // Zeroing the serverAddr struct as suggested by IEEE (https://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html) using the bzero function (from <strings.h>)
  bzero(&serverAddr, sizeof(serverAddr));

  /*
    NB: 
    AF_INET = Address Format, Internet = IP Addresses
    PF_INET = Packet Format, Internet = IP, TCP/IP or UDP/IP
  */

  /**
     SA_IN Configuration
  */
  serverAddr.sin_family = AF_INET;

  /*
    Set port number, using htons function to use proper byte order
    We are using htons to convert PORT to a "netwrok byte order"
  */
  serverAddr.sin_port = htons(PORT);

  /* Make the server listening to any interfaces in order to make it available on the network */
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /**
     Socket Binding
     The INADDR_ANY binding does not generate a random IP address
     It maps the socket to all available interfaces (which on a server for obvious reasons is something strongly desired),
     and not just localhost.
  */

  check((bind(serverSocket, (SA *)&serverAddr, sizeof(serverAddr))), "[-]Errore sulla bind");
  logging("[+] Binding inizializzato correttamente");

  /**
     Socket Listen

  */
  check((listen(serverSocket, SERVER_BACKLOG)), "[-]Errore sulla listen");
  info_logging(PORT, SERVER_BACKLOG);

  for(;;){
    printf("[+] In attesa di connessioni...\n");

    addressLen = sizeof(SA_IN);

    check((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, (socklen_t *)&addressLen )), "[-]Errore sulla accept");
    client_logging((char*)inet_ntoa((struct in_addr)clientAddr.sin_addr));
    
  }
}
