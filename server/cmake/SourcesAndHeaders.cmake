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

    # Command line flag parser
    src/infrastructure/command_line_runner/command_line_runner.c

    # Configuration parser with ini config file
    src/infrastructure/config/config_parser.c
    src/infrastructure/config/info_point_config.c
    

    # Database Related
    # src/core/database/database.c
)

set(headers

    # Utility functions
    src/infrastructure/logging/logging.h
    src/infrastructure/utility/utility.h

    # Server related
    src/core/server/server.h
    src/core/handler/handler.h

    # Msg communication wrapper
    src/core/message/message.h

    # Workers related
    src/infrastructure/pool/thread_pool.h

    # Command line flag parser
    src/infrastructure/command_line_runner/command_line_runner.c

    # Configuration parser with ini config file
    src/infrastructure/config/config_parser.h
    src/infrastructure/config/info_point_config.h
    src/infrastructure/config/sys_queue.h

    # Database Related
    # src/core/database/database.h
)
