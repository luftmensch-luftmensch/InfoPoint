---
title: Struttura del progetto
weight: 10
---

La struttura del server è così strutturata:

```bash
src ------------------------------------------- Root del progetto
├── core -------------------------------------- Strutture fondamentali per la corretta esecuzione del server
│   ├── database ------------------------------ Supporto alla comunicazione con il database
│   │   ├── database.c
│   │   └── database.h
│   ├── handler ------------------------------- Struttura handler per comunicazione con il server
│   │   ├── handler.c
│   │   └── handler.h
│   ├── message ------------------------------- Funzioni di supporto per la comunicazione mediante socket
│   │   ├── message.c
│   │   └── message.h
│   ├── payload ------------------------------- Payload della comunicazione server <-> client
│   │   ├── artwork
│   │   ├── client
│   │   │   ├── client.c
│   │   │   └── client.h
│   │   └── request
│   │       └── request.h
│   └── server  ------------------------------- Definizione della struttura "server"
│       ├── server.c
│       └── server.h
├── info_point.ini ---------------------------- File di configurazione
├── infrastructure ---------------------------- Strutture di supporto
│   ├── base ---------------------------------- Definizione di tipi e funzioni di supporto
│   │   └── types_definition.h
│   ├── command_line_runner ------------------- Wrapper per il passaggio dei parametri al programma
│   │   ├── command_line_runner.c
│   │   └── command_line_runner.h
│   ├── config -------------------------------- Supporto alla gestione/parsing della configurazione
│   │   ├── config.c
│   │   ├── config.h
│   │   └── main.c
│   ├── logging ------------------------------- Supporto al logging
│   │   ├── logging.c
│   │   ├── logging.h
│   │   └── welcome_message.h
│   ├── pool ---------------------------------- Supporto alla comunicazione multi-threading
│   │   ├── thread_pool.c
│   │   └── thread_pool.h
│   └── utility ------------------------------- Funzioni di utility generiche
│       ├── utility.c
│       └── utility.h
└── main.c ------------------------------------ Main entry point
```


{{% notice note %}}
Per una forte coesione e coerenza tutte le strutture custom di InfoPoint mettono a disposizione API con pattern pressochè identici (si faccia caso alla naming convention utilizzata).
{{% /notice %}}

Andiamo adesso, per ogni componente, a descrivere meglio il loro compito.


## `Core`
Contiene le componenti fondamentali alla definizione del progetto.


### `Database`
Contiene la struttura e la logica del gestore (handler) che ha il compito di comunicare con l'istanza del Database `NOSQL` MongoDB.

Mette a dispozione delle API per le operazioni basilari (inserimento, retrieval, eliminazione delle informazioni) delle collezioni di `Utenti` e `Opere` presenti nel museo

### `Handler`
### `Server`
È il cuore dell'applicativo. Svolge il compito di *orchestratore* di tutto il programma.

### `Message`
Contiene delle funzioni wrapper utili alla comunicazione tramite socket (di cui l'applicativo fa largo uso)

### `Payload`
Prendendo ispirazione dal protocollo `HTTP` facciamo uso del concetto di Payload, oggetto che rappresenta informazioni (su Utenti e Opere) che i client e il server si scambieranno.

## `Infrastructure`
Contiene le componenti necessarie alla definizione dell'infrastruttura.

### `Base`
Contiene la definizione di
+ Alias di tipi comuni (sfruttando la keyword `typedef`) per una più facile modifica nel tempo;
+ Macro per operazioni elementari.

### `CommandLineRunner`
Fa da wrapper alla libreria `argp.h` per il parsing dei parametri passati all'eseguibile prodotto in fase di compilazione

### `Config`
Ha il compito di recuperare le informazioni presenti all'interno del file di configurazione (in formato `ini`) messo a dispozione per il settaggio delle opzioni necessarie all'esecuzione del server.

### `Logging`
Utility per il logging delle operazioni effettuate dal server durante la sua esecuzione

### `Pool`
`Thread-Pool` utilizzata dal server per soddisfare le richieste in ingresso.

### `Utility`
Contiene funzioni per:
+ Lettura e recupero informazioni di file;
+ Definizione di Regex utilizzate dal programma;
+ Manipolazione di buffer (trimming e concatenazione).
