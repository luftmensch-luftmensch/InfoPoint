set(sources
    # Main entry
    src/main.c

    # Utility functions
    src/infrastructure/logging/logging.c
    src/infrastructure/utility/utility.c

    # Server related
    src/core/server/server.c
    src/core/handler/handler.c

    # Msg communication wrapper
    src/core/message/message.c

    # Workers related
    src/infrastructure/pool/thread_pool.c

    # Configuration parser with ini config file
    src/infrastructure/config/config.c

    # Database Related
    # src/core/database/database.c
)

set(headers

    # Utility functions
    src/infrastructure/logging/logging.c
    src/infrastructure/utility/utility.c

    # Server related
    src/core/server/server.h
    src/core/handler/handler.h

    # Msg communication wrapper
    src/core/message/message.h

    # Workers related
    src/infrastructure/pool/thread_pool.c

    # Configuration parser with ini config file
    src/infrastructure/config/config.h

    # Database Related
    # src/core/database/database.h
)
