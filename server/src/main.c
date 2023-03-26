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
#include "common/logging/welcome_message.h"

int main(){
  // Welcome message
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET , welcome_msg);

  server* s = init_server(9090, 10);

  printf("%lu\n", s->conn_count);
}
