/*
  ╦ ╦┬─┐┌─┐┌─┐┌─┐┌─┐┬─┐
  ║║║├┬┘├─┤├─┘├─┘├┤ ├┬┘
  ╚╩╝┴└─┴ ┴┴  ┴  └─┘┴└─
  Autori:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#include "wrapper.h"

#define _m(type, format, ...) _msgcategory(type, "WRAP", format, ##__VA_ARGS__)

ssize_t wrap_send(int sockfd, const void* const buf, size_t len, int flags){
  char cp[len + 1];
  memcpy(cp, buf, len);
  ssize_t bytes = send(sockfd, cp, len + 1, flags | MSG_NOSIGNAL);
  #if defined(DEBUG)
    static long long unsigned send_event = 0;
    size_t index = 0;
    while(index < len){
      if(cp[index] == '\n')
	cp[index] = '@';
      index++;
    }
    _mW(_msgdebug, "[SENT][e: %ld][%ldB to &%ld] <%s\\0>", send_event, bytes, sockfd, cp);
    send_event++;

  #endif
  
  return bytes;
}

ssize_t wrap_recv(int sockfd, void* buf, ssize_t len, int flags, bool * const read_again){
  //memset(buf, 0, len);
  bzero(buf, sizeof(len));

  ssize_t c_total = 0;
  ssize_t c_reading = 0;
  // Exhaust buffer size with the message if possibile
  do {
    c_reading = recv(sockfd, &((char*)buf)[c_total], len - c_total, flags);
    if (c_reading == -1){
      _m(_msgwarn, "[RECV] Returned and error");
      perror("[RECV]");
      *read_again = false;
      return c_reading;
    }
    c_total += c_reading;
  } while(c_reading > 0 && c_total < len && ((char*)buf)[c_total] != '\0');
  // Check if there is still content on the buffer
  char tmp;
  if(((char*)buf)[c_reading - 1] == '\0')
    *read_again = false;
  // ENHANCE: Read to dev/null/ as I don't need that
  else
    *read_again = recv(sockfd, &tmp, 1, flags | MSG_PEEK) != -1;


  #if defined(DEBUG) 
    static long long unsigned recv_event = 0;
    _m(_msgdebug, "[RECV][e:%ld][%ldB from &%ld] <%.*s\\0>", recv_event, c_total, sockfd, 
       ((char*)buf)[c_total - 1] == '\n'	?  c_total - 1 : c_total, buf);
    recv_event++;
  #endif

  return c_total;
}
