/*
  ╔╦╗  ╦ ╦  ╔═╗  ╔═╗  ╔═╗        ╔╦╗  ╔═╗  ╔═╗  ╦  ╔╗╔  ╦  ╔╦╗  ╦  ╔═╗  ╔╗╔
   ║   ╚╦╝  ╠═╝  ║╣   ╚═╗         ║║  ║╣   ╠╣   ║  ║║║  ║   ║   ║  ║ ║  ║║║
   ╩    ╩   ╩    ╚═╝  ╚═╝        ═╩╝  ╚═╝  ╚    ╩  ╝╚╝  ╩   ╩   ╩  ╚═╝  ╝╚╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#ifndef _TYPES_DEFINITION_H_
#define _TYPES_DEFINITION_H_

  #include <stdio.h>

  // Unsigned int types.
  typedef unsigned char u8;
  typedef unsigned short u16;
  typedef unsigned int u32;
  typedef unsigned long long u64;

  // Signed int types.
  typedef signed char s8;
  typedef signed short s16;
  typedef signed int s32;
  typedef signed long long s64;

  // Regular int types.
  typedef char i8;
  typedef short i16;
  typedef int i32;
  typedef long long i64;

  // Floating point types
  typedef float f32;
  typedef double f64;

  // Boolean types
  typedef u8  b8;
  typedef u32 b32;

  // Basic operations using macros
  #define Min(a,b) (((a)<(b))?(a):(b))
  #define Max(a,b) (((a)>(b))?(a):(b))

  #define Clamp(a,x,b) (((x)<(a))?(a):((b)<(x))?(b):(x))
  #define ClampTop(a,b) Min(a,b)
  #define ClampBot(a,b) Max(a,b)
  #define ReverseClamp(a,x,b) (((x)<(a))?(b):((b)<(x))?(a):(x))

  #define Wrap(a,x,b) ReverseClamp(a,x,b)

  #define MemoryCopy(d,s,z) memmove((d), (s), (z))
  #define MemoryCopyStruct(d,s) MemoryCopy((d),(s), Min(sizeof(*(d)) , sizeof(*(s))))
  #define MemoryZero(d,z) memset((d), 0, (z))
  #define MemoryZeroStruct(d,s) MemoryZero((d),sizeof(s))

  #define ArrayCount(a) (sizeof(a) / sizeof(a[0]))

#endif
