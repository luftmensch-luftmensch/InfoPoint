set(sources
    # Main entry
    src/main.c

    # Base utility fun
    src/utils/common/utils.c

    # Socket utility
    src/utils/socket/handler/handler.c
    src/utils/socket/wrapper/wrapper.c
    src/utils/socket/server/server.c

    # Database utilities
    src/database/database.c
)

set(headers
    src/utils/common/welcome_message.h
    src/utils/common/utils.h

    src/utils/socket/wrapper/wrapper.h
    src/utils/socket/handler/handler.h
    src/utils/socket/server/server.h

    src/database/database.h
)
