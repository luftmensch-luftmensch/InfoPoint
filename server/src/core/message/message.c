/*
  ╔╦╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔═╗
  ║║║  ║╣   ╚═╗  ╚═╗  ╠═╣  ║ ╦  ║╣ 
  ╩ ╩  ╚═╝  ╚═╝  ╚═╝  ╩ ╩  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include "message.h"

#define _m(type, format, ...) _msgcategory(type, "MSG", format, ##__VA_ARGS__)


ssize_t msg_send(int sock_fd, const void* const buf, size_t len, int flags) {
  char copy[len + 1];
  memcpy(copy, buf, len);
  copy[len] = '\0'; // Null terminate string
  ssize_t bytes = send(sock_fd, copy, len + 1, flags | MSG_NOSIGNAL);

  // Run only in debug mode
  #if defined(DEBUG)
    static long long unsigned ev = 0;
    size_t index = 0;
    while(index < len) {
      if (copy[index] == '\n')
	copy[index] = '@';
      index++
    }
    _m(_msgdebug, "[SENT][e: %ld][%ldB to &%ld] <%s\\0>", ev, bytes, sock_fd, copy);
    ev++;
  #endif

  return bytes;
  
}
ssize_t msg_recv(int sock_fd, void* buf, ssize_t len, int flags, bool* const read_again) {
  memset(buf, 0, len);

  ssize_t c_total = 0;
  ssize_t c_read = 0;

  do {
    c_read = recv(sock_fd, &((char*) buf)[c_total], len - c_total, flags);
    if (c_read == -1){
      _m(_msgwarn, "Got an error while reciving msg");
      perror("recv: ");
      *read_again = false;
      return c_read;
    }
    c_total += c_read;

  } while(c_read > 0 && c_total < len && ((char*)buf)[c_total] != '\0' );

  // Check if there is still something to read on the buffer

  char tmp;
  if (((char*) buf)[c_read -1] == '\0')
    *read_again = false;
  else
    *read_again = recv(sock_fd, &tmp, 1, flags | MSG_PEEK) != -1;


  // Run only in debug mode
  #if defined(DEBUG) 
	  static long long unsigned ev = 0;
	  _m(_msgdebug, "[RECV][e:%ld][%ldB from &%ld] <%.*s\\0>", ev, c_total, sock_fd, 
		  ((char*)buf)[c_total - 1] == '\n'	?  c_total - 1 : c_total, buf);
	  ev++;
  #endif
  
  return c_total;
}
