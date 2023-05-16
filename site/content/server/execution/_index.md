---
title: Esecuzione del server
weight: 15
---

I seguenti passi sono necessari per far si che la piattaforma possa funzionare correttamente

## Prima di inziare


{{% notice note %}}
Per far si che tutto funzioni correttamente assicurati di aver effettuato tutti i punti specificati [precedentemente]({{< relref "getting-started/installation" >}})
{{% /notice %}}

## Esecuzione dell'applicativo

Una volta soddisfatto le [dipendenze]({{<relref "getting-started/installation/#installazione-del-server">}}) richieste è possibile eseguire il server in locale (eseguendo `build/InfoPointServer`, sorgente prodotto dall'utility **cmake**)

{{% notice tip %}}
Per modificare i parametri di esecuzione del server è possibile fare uso del suo file di configurazione.
{{% /notice %}}


Di default viene offerta un template base (`info_point.ini`)

```ini
;; Info Point configuration file
[network]
; Bind to a single interface
; If not specified all the interfaces will listen for incoming connections.
host = localhost
; Accept connections on the specified port, default is 9090.
; If port 0 is specified the server will not listen on a TCP socket.
port = 9090

; Close the connection after a client is idle for N seconds (0 to disable)
timeout = 0

[connections]
; Set the max number of connected clients at the same time.
; By default this limit is set to 100 clients.
; Once the limit is reached the server will close all the new connections.
max_clients = 100

; Set the max number of worker threads.
max_threads = 100

[logging]
; Set server verbosity. Available options:
;  + debug (a lot of information, useful for development/testing)
;  + verbose (many rarely useful info, but not a mess like the debug level)
;  + notice (moderately verbose, what you want in production probably)
;  + warning (only very important / critical messages are logged)
log_level = debug
; Specify the log file name.
; Also 'stdout' can be used to force the server to log on the standard output.
; Note that if you use standard output for logging but daemonize,
; logs will be sent to /dev/null
log_file = stdout

[database]
; Type of the database to connect with.
; Currently only mongodb is supported
type = mongodb
; Host on which the database is running
host = localhost
; Port on which the database is listening to
port = 27017
```


Una volta invocato il server [^1], questo:
1. Effettuerà il parsing delle flag passate come argomento (si veda la sezione [inerente]({{< relref "server/structure/#commandlinerunner" >}}))

    a. Nel caso in cui venga specificato un file di configurazione, il server setterà la sua configurazione basandosi sul contenuto del file;

    b. In caso contrario, il server utilizzerà una configurazione di default;
2. Una volta costruita la configurazione il programma gestirà l'inizializzazione di
    - ***server***, il cuore di tutto l'applicativo (la cosìddetta `main entry point`);
    - ***db_handler***, il gestore per la connessione/comunicazione con il database;
    - ***thread_pool*** e ***handler***, le strutture di supporto alle funzionalità del server
3. Infine il server si metterà in ascolto per le richieste in ingresso da parte dei client che proverrano a collegarsi.


[^1]: Invocando il comando `./build/InfoPointServer` (e opzionalmente specificando il path del file di configurazione con `-f /path/to/the/config.ini`)