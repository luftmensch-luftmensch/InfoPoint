#ifndef InfoPoint_Wrapper
#define InfoPoint_Wrapper

  #include <stdio.h>
  #include <sys/socket.h>
  #include <stdbool.h>
  #include <string.h>
  #include "../common/utils.h"


  // Wrapper functions for send/recv operations
  ssize_t wrap_send(int sockfd, const void* const buf, size_t len, int flags);
  ssize_t wrap_recv(int sockfd, void* buf, ssize_t len, int flags, bool * const read_again);

#endif
