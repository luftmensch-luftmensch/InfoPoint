---
title: Installazione
weight: 10
---

I seguenti passi sono necessari per far si che la piattaforma possa funzionare correttamente

## Prima di inziare

Per far si che tutto funzioni correttamente è necessario soddisfare le sseguenti dipendenze:

#### App

* Il linguaggio [java](https://www.oracle.com/java/technologies/downloads/) >= 17, che è stato utilizzato per produrre l'applicazione;

#### Server

* Il compilatore [gcc](https://gcc.gnu.org/install/download.html) >= 11.3.0;
* L'utility [cmake]() per la compilazione del codice sorgente;
* Il database NOSQL [mongodb](https://www.mongodb.com/download-center/community/releases) e il corrispettivo driver C [mongoc](https://mongoc.org/) utilizzato per la comunicazione con quest ultimo;
* _[Opzionale]_ [docker](https://www.docker.com/products/docker-desktop/) e [docker-compose](https://docs.docker.com/compose/install/) per eseguire in maniera containerizzata la piattaforma;
* _[Opzionale]_ Lo strumento di versionamento [git](https://git-scm.com/downloads) per il download del codice sorgente;
 
#### IDE consigliati

Si consiglia l'utilizzo dell'IDE [Android Studio](https://developer.android.com/studio/) per la gestione ed esecuzione dell'applicazione mobile e uno tra [Emacs](https://www.gnu.org/software/emacs/download.html), [CLion](https://www.jetbrains.com/clion/download/), [VSCode](https://code.visualstudio.com/Download) per la gestione ed esecuzione del *Server*.


## Installazione

Una volta soddisfatto le dipendenze sopra citate è possibile clonare (con git) o scaricare il codice sorgente al seguente [indirizzo](https://github.com/luftmensch-luftmensch/InfoPoint)

#### Installazione dell'applicazione
Scaricato il codice sorgente è possibile aprire la cartella [client](https://github.com/luftmensch-luftmensch/InfoPoint/tree/main/client) con l'IDE scelto e iniziare la fase di build (che produrrà l'apk da installare sul dispositivo) o in alternativa eseguire direttamente il progetto in modo tale che la fase di installazione sia automatizzata

AGGIUNGERE SCREENSHOT

#### Installazione del server
Scaricato il codice sorgente è possibile aprire la cartella [server](https://github.com/luftmensch-luftmensch/InfoPoint/tree/main/server) con l'IDE scelto e iniziare la fase di build automatizzata con l'utility **cmake**

AGGIUNGERE SCREENSHOT
