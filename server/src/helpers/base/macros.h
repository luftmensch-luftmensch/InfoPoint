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


  // Basic operations using macros
  #define Clamp(a,x,b) (((x)<(a))?(a):((b)<(x))?(b):(x))
  #define ClampTop(a,b) Min(a,b)
  #define ClampBot(a,b) Max(a,b)
  #define ReverseClamp(a,x,b) (((x)<(a))?(b):((b)<(x))?(a):(x))

  #define Wrap(a,x,b) ReverseClamp(a,x,b)

  #define MemoryCopy(d,s,z) memmove((d), (s), (z))
  #define MemoryCopyStruct(d,s) MemoryCopy((d),(s), Min(sizeof(*(d)) , sizeof(*(s))))
  #define MemoryZero(d,z) memset((d), 0, (z))
  #define MemoryZeroStruct(d,s) MemoryZero((d),sizeof(s))

  #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

  #define typename(x) _Generic((x),        /* Get the name of a type */             \
										    \
	  _Bool: "_Bool",                  unsigned char: "unsigned char",          \
	   char: "char",                     signed char: "signed char",            \
      short int: "short int",         unsigned short int: "unsigned short int",     \
	    int: "int",                     unsigned int: "unsigned int",           \
       long int: "long int",           unsigned long int: "unsigned long int",      \
  long long int: "long long int", unsigned long long int: "unsigned long long int", \
	  float: "float",                         double: "double",                 \
    long double: "long double",                   char *: "pointer to char",        \
	 void *: "pointer to void",                int *: "pointer to int",         \
	default: "other")

#endif
