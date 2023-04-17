---
title: Struttura del progetto
weight: 15
---

La struttura del progetto è così suddivisa:

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
├── infrastructure
│   ├── base ---------------------------------- Definizione di tipi e funzioni di supporto
│   │   └── types_definition.h
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

Andiamo adesso, per ogni componente, a descrivere meglio il loro compito.


## `Core`
Contiene le componenti fondamentali alla definizione del progetto.

### `Database`
### `Handler`
### `Server`
### `Message`
### `Payload`

## `Infrastructure`
Contiene le componenti necessarie alla definizione dell'infrastruttura.

### `Base`
### `Config`
### `Logging`
### `Pool`
### `Utility`
