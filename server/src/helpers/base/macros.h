/*
  ╔╦╗  ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╔═╗
  ║║║  ╠═╣  ║    ╠╦╝  ║ ║  ╚═╗
  ╩ ╩  ╩ ╩  ╚═╝  ╩╚═  ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _MACROS_H_
#define _MACROS_H_

  /* A better __FILE__ macro */
  #ifndef __FILE_NAME__
    #define __FILE_NAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
  #endif

#endif
