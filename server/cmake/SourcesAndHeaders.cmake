set(sources
    # Main entry
    src/main.c

    # Utility functions
    src/common/logging/logging.c
    src/common/utility/utility.c

    # Server related
    src/core/server/server.c
    src/core/handler/handler.c

    # Msg communication wrapper
    src/core/message/message.c

    # Workers related
    src/core/pool/thread_pool.c
    src/common/container/node/node.c
    src/common/container/list/linked_list.c
    src/common/container/list/queue.c

    # Database Related
    # src/core/database/database.c
)

set(headers

    # Utility functions
    src/common/logging/logging.c
    src/common/utility/utility.c

    # Server related
    src/core/server/server.h
    src/core/handler/handler.h

    # Msg communication wrapper
    src/core/message/message.h

    # Workers related
    src/core/pool/thread_pool.h
    src/common/container/node/node.h
    src/common/container/list/linked_list.h
    src/common/container/list/queue.h

    # Database Related
    # src/core/database/database.h
)
