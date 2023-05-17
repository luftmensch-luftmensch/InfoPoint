set(sources
    # Main entry
    src/main.c

    # Utility functions
    src/helpers/logging/logging.c
    src/helpers/utility/utility.c

    # Server related
    src/core/server/server.c
    src/core/handler/handler.c

    # Msg communication wrapper
    src/core/message/message.c

    # Workers related
    src/helpers/pool/thread_pool.c

    # Command line flag parser
    src/helpers/command_line_runner/command_line_runner.c

    # Configuration parser with ini config file
    src/helpers/config/config_parser.c
    src/helpers/config/info_point_config.c
    

    # Database Related
    src/core/database/database.c
)

set(headers

    # Utility functions
    src/helpers/logging/logging.h
    src/helpers/utility/utility.h

    # Server related
    src/core/server/server.h
    src/core/handler/handler.h

    # Msg communication wrapper
    src/core/message/message.h

    # Workers related
    src/helpers/pool/thread_pool.h

    # Command line flag parser
    src/helpers/command_line_runner/command_line_runner.c

    # Configuration parser with ini config file
    src/helpers/config/config_parser.h
    src/helpers/config/info_point_config.h
    src/helpers/config/sys_queue.h

    # Database Related
    src/core/database/database.h
)
