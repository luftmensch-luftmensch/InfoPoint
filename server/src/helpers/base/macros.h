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

  /* A better max macro avoiding the "double-evaluation" side effects and bug */
  #define max(a,b)		\
  ({				\
      __typeof__ (a) _a = (a);	\
      __typeof__ (b) _b = (b);	\
      _a > _b ? _a : _b;	\
  })

  /* A better min macro avoiding the "double-evaluation" side effects and bug */
  #define min(a,b)             \
  ({                           \
      __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
      _a < _b ? _a : _b;       \
  })


#endif
