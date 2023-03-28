/*
  ╦  ╔╗╔  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╦  ╔╗╔  ╔╦╗
  ║  ║║║  ╠╣   ║ ║  ╠═╝  ║ ║  ║  ║║║   ║ 
  ╩  ╝╚╝  ╚    ╚═╝  ╩    ╚═╝  ╩  ╝╚╝   ╩ 
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )

*/


#include "core/server/server.h"
#include "infrastructure/logging/welcome_message.h"
#include <stdint.h>

#include "infrastructure/pool/thread_pool.h"
#include <pthread.h>

void task(void *arg){
    printf("Thread #%u working on %d\n", (int)pthread_self(), (int)(uintptr_t) arg);
}

int main(){
  // Welcome message
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET , welcome_msg);

  //server* s = init_server(9090, 10);

  //printf("%lu\n", s->conn_count);
  puts("Making threadpool with 4 threads");
  struct thread_pool* thpool = init_thread_pool(4);

  puts("Adding 40 tasks to threadpool");
  int i;
  for (i=0; i<40; i++){
    add_work_to_thread_pool(thpool, task, (void*)(uintptr_t)i);
  };

  await_thread_pool(thpool);
  puts("Killing threadpool");
  destroy_thread_pool(thpool);
}
