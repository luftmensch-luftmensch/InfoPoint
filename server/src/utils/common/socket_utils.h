#ifndef InfoPoint_Utils
#define InfoPoint_Utils

  #define SOCKET_ERROR (-1)
  /*
    Gestore degli errori delle funzioni `socket`, `bind`, `listen`, `accept` e `read`
    (Sfruttiamo il fatto che tutti questi metodi abbiano come valore di ritorno in caso di errore `-1`).
    Per brevità utilizziamo questa funzione con lo scopo di evitare di scrivere
    molteplici `if statement` che controllino il `return value`
  */
  int check(int expr, const char *msg);

#endif
