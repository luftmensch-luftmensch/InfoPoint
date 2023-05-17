---
title: Installazione ed prima esecuzione
weight: 20
---

I seguenti passi sono necessari per far si che ***InfoPoint*** possa essere eseguito correttamente

## Prima di iniziare

Come precedentemente [specificato]({{<relref "getting-started/installation/#server">}}) i seguenti programmi sono necessari per procedere con i passi successivi:
+ `docker`;
+ `docker-compose`;

## Operazioni per il deploy

Una volta soddisfatto le dipendenze richieste, utilizziamo i seguenti file per la compilazione ed esecuzione dell'applicativo in maniera containerizzata:

+ `Dockerfile`;
+ `docker-compose`.

{{% notice note %}}
Entrambi i file si trovano alla radice del codice sorgente del server.
{{% /notice %}}

### Analisi del `Dockerfile`
Di seguito viene portata per esteso il contenuto del Dockerfile, contenente tutte le istruzioni necessarie alla corretta compilazione dell'applicativo [^1]


```dockerfile
### InfoPoint Dockerfile ###

#
# BUILD STAGE
#

# Living on the edge
FROM archlinux:base as base

# Global variables
ARG C_COMPILER=gcc
ARG BUILD_TYPE=Release

### Update & install required pkgs ###
RUN echo -e "\033[1;34m Updating the machine [arch]...\033[0m"
RUN pacman -Syy

RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Installing dependencies...\033[0m"
RUN pacman -S --noconfirm \
    # Build utilities
    make cmake \
    # Compiler used
    ${C_COMPILER} \
    mongo-c-driver # Mongodb driver (needed to connect to the mongodb instance)

RUN echo -e "\033[1;34m Done!\033[0m"


### Configure needed variables ###
ENV CC=${C_COMPILER}

WORKDIR /builder

### Build project w/ cmake ###
RUN echo -e "\033[1;34m Copying directories...\033[0m"
COPY . .
RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Configuring cmake options...\033[0m"
RUN CC=${C_COMPILER} cmake -S . -B build/ -D CMAKE_BUILD_TYPE=${BUILD_TYPE}
RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Building project...\033[0m"
RUN CC=${C_COMPILER} cmake --build build/
RUN echo -e "\033[1;34m Done!\033[0m"

RUN echo -e "\033[1;34m Installing the executable...\033[0m"
RUN CC=${C_COMPILER} cmake --install build/ --prefix install/ --config ${BUILD_TYPE}
RUN echo -e "\033[1;34m Done!\033[0m"

### Expose the executable ###
ENTRYPOINT [ "/builder/install/bin/InfoPointServer" ]
```

### Analisi del `docker-compose.yml`
Di seguito viene portata per esteso il contenuto del file ***docker-compose.yml***, contenente le istruzioni per:
+ Buildare il server;
+ Generare il container docker per il database utilizzato (Mongodb);
+ Creazione della rete di comunicazione tra server e database;


```yaml
### InfoPoint microservice backend ###
version: '3.9'
services:

  ### Server ###
  server:
    container_name: infopoint-server
    build:
      context: .
      dockerfile: Dockerfile
    ports:
      - "9090:9090"
    expose:
      - "9090"
    depends_on:
      database:
          condition: service_healthy
  ### Database ###
  database:
    # Official Mongo image from DockerHub (latest)
    image: mongo
    container_name: infopoint-mongodb
    # By default, a Mongo database is running on the 27017 port.
    # If we want to access the database from our computer (outside the container),
    # we must share the port with our computer's port.
    # The syntax is [port we want on our machine]:[port we want to retrieve in the container]
    # Note: You are free to change your computer's port,
    # but take into consideration that it will change the way
    # you are connecting to your database.
    ports:
      - 27017:27017
    expose:
      - "27017"
    # Environment variables
    environment:
      - MONGO_INITDB_ROOT_USERNAME=admin
      - MONGO_INITDB_ROOT_PASSWORD=password
    healthcheck:
      test: echo 'db.runCommand("ping").ok' | mongosh localhost:27017/admin --quiet
      interval: 30s
      timeout: 10s
      retries: 5
```

### Esecuzione

Infine, spostandosi nella directory specificata, invocando, da terminale:

```bash
$ docker-compose up -d
```

`Docker` si occuperà di:
1. Recuperare le immagini [^2] necessarie specificate nei 2 file;
2. Buildare il programma partendo dal il codice sorgente specificato;
3. Lanciare in esecuzione il database Mongodb, e una volta attivo, anche il server;

[^1]: Si noti l'uso di [multi-stage-built](https://docs.docker.com/build/building/multi-stage/).
[^2]: Per immagini si intende un software che contiene tutte le dipendenze per eseguire l'applicazione.
