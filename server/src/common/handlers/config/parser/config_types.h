/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗      ╔╦╗  ╦ ╦  ╔═╗  ╔═╗  ╔═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦       ║   ╚╦╝  ╠═╝  ║╣   ╚═╗
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝       ╩    ╩   ╩    ╚═╝  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/

#ifndef _CONFIG_TYPES_H
#define _CONFIG_TYPES_H

  #include <stdint.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdarg.h>

  typedef enum classes {
    C_SPACE, /* space */
    C_NL,    /* newline */
    C_WHITE, /* tab, CR */
    C_LCURB, C_RCURB, /* object opening/closing */
    C_LSQRB, C_RSQRB, /* array opening/closing */
    /* syntax symbols */
    C_COLON,
    C_COMMA,
    C_QUOTE, /* " */
    C_BACKS, /* \ */
    C_SLASH, /* / */
    C_PLUS,
    C_MINUS,
    C_DOT,
    C_ZERO, C_DIGIT, /* digits */
    C_a, C_b, C_c, C_d, C_e, C_f, C_l, C_n, C_r, C_s, C_t, C_u, /* nocaps letters */
    C_ABCDF, C_E, /* caps letters */
    C_OTHER, /* all other */
    C_STAR, /* star in C style comment */
    C_HASH, /* # for YAML comment */
    C_ERROR = 0xfe,
  } classes;

  /* map from character < 128 to classes. from 128 to 256 all C_OTHER */
  static uint8_t character_class[128] = {
    C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR,
    C_ERROR, C_WHITE, C_NL,    C_ERROR, C_ERROR, C_WHITE, C_ERROR, C_ERROR,
    C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR,
    C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR, C_ERROR,

    C_SPACE, C_OTHER, C_QUOTE, C_HASH,  C_OTHER, C_OTHER, C_OTHER, C_OTHER,
    C_OTHER, C_OTHER, C_STAR,  C_PLUS,  C_COMMA, C_MINUS, C_DOT,   C_SLASH,
    C_ZERO,  C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT,
    C_DIGIT, C_DIGIT, C_COLON, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER,

    C_OTHER, C_ABCDF, C_ABCDF, C_ABCDF, C_ABCDF, C_E,     C_ABCDF, C_OTHER,
    C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER,
    C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_OTHER,
    C_OTHER, C_OTHER, C_OTHER, C_LSQRB, C_BACKS, C_RSQRB, C_OTHER, C_OTHER,

    C_OTHER, C_a,     C_b,     C_c,     C_d,     C_e,     C_f,     C_OTHER,
    C_OTHER, C_OTHER, C_OTHER, C_OTHER, C_l,     C_OTHER, C_n,     C_OTHER,
    C_OTHER, C_OTHER, C_r,     C_s,     C_t,     C_u,     C_OTHER, C_OTHER,
    C_OTHER, C_OTHER, C_OTHER, C_LCURB, C_OTHER, C_RCURB, C_OTHER, C_OTHER
  };

  /* only the first 36 ascii characters need an escape */
  static char const *character_escape[] = {
    "\\u0000", "\\u0001", "\\u0002", "\\u0003", "\\u0004", "\\u0005", "\\u0006", "\\u0007", /*  0-7  */
    "\\b"    ,     "\\t",     "\\n", "\\u000b",     "\\f",     "\\r", "\\u000e", "\\u000f", /*  8-f  */
    "\\u0010", "\\u0011", "\\u0012", "\\u0013", "\\u0014", "\\u0015", "\\u0016", "\\u0017", /* 10-17 */
    "\\u0018", "\\u0019", "\\u001a", "\\u001b", "\\u001c", "\\u001d", "\\u001e", "\\u001f", /* 18-1f */
    "\x20"   , "\x21"   , "\\\""   , "\x23"   , "\x24"   , "\x25"   , "\x26"   , "\x27"   , /* 20-27 */
    "\x28"   , "\x29"   , "\x2a"   , "\x2b"   , "\x2c"   , "\x2d"   , "\x2e"   , "\x2f"   , /* 28-2f */
    "\x30"   , "\x31"   , "\x32"   , "\x33"   , "\x34"   , "\x35"   , "\x36"   , "\x37"   , /* 30-37 */
    "\x38"   , "\x39"   , "\x3a"   , "\x3b"   , "\x3c"   , "\x3d"   , "\x3e"   , "\x3f"   , /* 38-3f */
    "\x40"   , "\x41"   , "\x42"   , "\x43"   , "\x44"   , "\x45"   , "\x46"   , "\x47"   , /* 40-47 */
    "\x48"   , "\x49"   , "\x4a"   , "\x4b"   , "\x4c"   , "\x4d"   , "\x4e"   , "\x4f"   , /* 48-4f */
    "\x50"   , "\x51"   , "\x52"   , "\x53"   , "\x54"   , "\x55"   , "\x56"   , "\x57"   , /* 50-57 */
    "\x58"   , "\x59"   , "\x5a"   , "\x5b"   , "\\\\"   , "\x5d"   , "\x5e"   , "\x5f"   , /* 58-5f */
    "\x60"   , "\x61"   , "\x62"   , "\x63"   , "\x64"   , "\x65"   , "\x66"   , "\x67"   , /* 60-67 */
    "\x68"   , "\x69"   , "\x6a"   , "\x6b"   , "\x6c"   , "\x6d"   , "\x6e"   , "\x6f"   , /* 68-6f */
    "\x70"   , "\x71"   , "\x72"   , "\x73"   , "\x74"   , "\x75"   , "\x76"   , "\x77"   , /* 70-77 */
    "\x78"   , "\x79"   , "\x7a"   , "\x7b"   , "\x7c"   , "\x7d"   , "\x7e"   , "\\u007f", /* 78-7f */
    "\\u0080", "\\u0081", "\\u0082", "\\u0083", "\\u0084", "\\u0085", "\\u0086", "\\u0087", /* 80-87 */
    "\\u0088", "\\u0089", "\\u008a", "\\u008b", "\\u008c", "\\u008d", "\\u008e", "\\u008f", /* 88-8f */
    "\\u0090", "\\u0091", "\\u0092", "\\u0093", "\\u0094", "\\u0095", "\\u0096", "\\u0097", /* 90-97 */
    "\\u0098", "\\u0099", "\\u009a", "\\u009b", "\\u009c", "\\u009d", "\\u009e", "\\u009f", /* 98-9f */
    "\\u00a0", "\\u00a1", "\\u00a2", "\\u00a3", "\\u00a4", "\\u00a5", "\\u00a6", "\\u00a7", /* a0-a7 */
    "\\u00a8", "\\u00a9", "\\u00aa", "\\u00ab", "\\u00ac", "\\u00ad", "\\u00ae", "\\u00af", /* a8-af */
    "\\u00b0", "\\u00b1", "\\u00b2", "\\u00b3", "\\u00b4", "\\u00b5", "\\u00b6", "\\u00b7", /* b0-b7 */
    "\\u00b8", "\\u00b9", "\\u00ba", "\\u00bb", "\\u00bc", "\\u00bd", "\\u00be", "\\u00bf", /* b8-bf */
    "\\u00c0", "\\u00c1", "\\u00c2", "\\u00c3", "\\u00c4", "\\u00c5", "\\u00c6", "\\u00c7", /* c0-c7 */
    "\\u00c8", "\\u00c9", "\\u00ca", "\\u00cb", "\\u00cc", "\\u00cd", "\\u00ce", "\\u00cf", /* c8-cf */
    "\\u00d0", "\\u00d1", "\\u00d2", "\\u00d3", "\\u00d4", "\\u00d5", "\\u00d6", "\\u00d7", /* d0-d7 */
    "\\u00d8", "\\u00d9", "\\u00da", "\\u00db", "\\u00dc", "\\u00dd", "\\u00de", "\\u00df", /* d8-df */
    "\\u00e0", "\\u00e1", "\\u00e2", "\\u00e3", "\\u00e4", "\\u00e5", "\\u00e6", "\\u00e7", /* e0-e7 */
    "\\u00e8", "\\u00e9", "\\u00ea", "\\u00eb", "\\u00ec", "\\u00ed", "\\u00ee", "\\u00ef", /* e8-ef */
    "\\u00f0", "\\u00f1", "\\u00f2", "\\u00f3", "\\u00f4", "\\u00f5", "\\u00f6", "\\u00f7", /* f0-f7 */
    "\\u00f8", "\\u00f9", "\\u00fa", "\\u00fb", "\\u00fc", "\\u00fd", "\\u00fe", "\\u00ff", /* f8-ff */
  };

  /* define all states and actions that will be taken on each transition.
   *
   * states are defined first because of the fact they are use as index in the
   * transitions table. they usually contains either a number or a prefix _
   * for simple state like string, object, value ...
   *
   * actions are defined starting from 0x80. state error is defined as 0xff
   */

  typedef enum states {
    STATE_GO, /* start  */
    STATE_OK, /* ok     */
    STATE__O, /* object */
    STATE__K, /* key    */
    STATE_CO, /* colon  */
    STATE__V, /* value  */
    STATE__A, /* array  */
    STATE__S, /* string */
    STATE_E0, /* escape */
    STATE_U1, STATE_U2, STATE_U3, STATE_U4, /* unicode states */
    STATE_M0, STATE_Z0, STATE_I0, /* number states */
    STATE_R1, STATE_R2, /* real states (after-dot digits) */
    STATE_X1, STATE_X2, STATE_X3, /* exponant states */
    STATE_T1, STATE_T2, STATE_T3, /* true constant states */
    STATE_F1, STATE_F2, STATE_F3, STATE_F4, /* false constant states */
    STATE_N1, STATE_N2, STATE_N3, /* null constant states */
    STATE_C1, STATE_C2, STATE_C3, /* C-comment states */
    STATE_Y1, /* YAML-comment state */
    STATE_D1, STATE_D2, /* multi unicode states */
  } states;

  /* the following are actions that need to be taken */
  typedef enum actions {
    STATE_KS = 0x80, /* key separator */
    STATE_SP, /* comma separator */
    STATE_AB, /* array begin */
    STATE_AE, /* array ending */
    STATE_OB, /* object begin */
    STATE_OE, /* object end */
    STATE_CB, /* C-comment begin */
    STATE_YB, /* YAML-comment begin */
    STATE_CE, /* YAML/C comment end */
    STATE_FA, /* false */
    STATE_TR, /* true */
    STATE_NU, /* null */
    STATE_DE, /* double detected by exponent */
    STATE_DF, /* double detected by . */
    STATE_SE, /* string end */
    STATE_MX, /* integer detected by minus */
    STATE_ZX, /* integer detected by zero */
    STATE_IX, /* integer detected by 1-9 */
    STATE_UC, /* Unicode character read */
  } actions;

  /* error state */
  #define STATE___ 	0xff

  #define NR_STATES 	(STATE_D2 + 1)
  #define NR_CLASSES	(C_HASH + 1)

  #define IS_STATE_ACTION(s) ((s) & 0x80)
  #define S(x) STATE_##x
  #define PT_(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,a1,b1,c1,d1,e1,f1,g1,h1)	\
	  { S(a),S(b),S(c),S(d),S(e),S(f),S(g),S(h),S(i),S(j),S(k),S(l),S(m),S(n),		\
	    S(o),S(p),S(q),S(r),S(s),S(t),S(u),S(v),S(w),S(x),S(y),S(z),S(a1),S(b1),		\
	    S(c1),S(d1),S(e1),S(f1),S(g1),S(h1) }

  /* map from the (previous state+new character class) to the next parser transition */
  static const uint8_t state_transition_table[NR_STATES][NR_CLASSES] = {
  /*             white                                                                            ABCDF  other    */
  /*         sp nl |  {  }  [  ]  :  ,  "  \  /  +  -  .  0  19 a  b  c  d  e  f  l  n  r  s  t  u  |  E  |  *  # */
  /*GO*/ PT_(GO,GO,GO,OB,__,AB,__,__,__,__,__,CB,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,YB),
  /*OK*/ PT_(OK,OK,OK,__,OE,__,AE,__,SP,__,__,CB,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,YB),
  /*_O*/ PT_(_O,_O,_O,__,OE,__,__,__,__,_S,__,CB,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,YB),
  /*_K*/ PT_(_K,_K,_K,__,__,__,__,__,__,_S,__,CB,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,YB),
  /*CO*/ PT_(CO,CO,CO,__,__,__,__,KS,__,__,__,CB,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,YB),
  /*_V*/ PT_(_V,_V,_V,OB,__,AB,__,__,__,_S,__,CB,__,MX,__,ZX,IX,__,__,__,__,__,F1,__,N1,__,__,T1,__,__,__,__,__,YB),
  /*_A*/ PT_(_A,_A,_A,OB,__,AB,AE,__,__,_S,__,CB,__,MX,__,ZX,IX,__,__,__,__,__,F1,__,N1,__,__,T1,__,__,__,__,__,YB),
  /****************************************************************************************************************/
  /*_S*/ PT_(_S,__,__,_S,_S,_S,_S,_S,_S,SE,E0,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S,_S),
  /*E0*/ PT_(__,__,__,__,__,__,__,__,__,_S,_S,_S,__,__,__,__,__,__,_S,__,__,__,_S,__,_S,_S,__,_S,U1,__,__,__,__,__),
  /*U1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,U2,U2,U2,U2,U2,U2,U2,U2,__,__,__,__,__,__,U2,U2,__,__,__),
  /*U2*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,U3,U3,U3,U3,U3,U3,U3,U3,__,__,__,__,__,__,U3,U3,__,__,__),
  /*U3*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,U4,U4,U4,U4,U4,U4,U4,U4,__,__,__,__,__,__,U4,U4,__,__,__),
  /*U4*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,UC,UC,UC,UC,UC,UC,UC,UC,__,__,__,__,__,__,UC,UC,__,__,__),
  /****************************************************************************************************************/
  /*M0*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,Z0,I0,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /*Z0*/ PT_(OK,OK,OK,__,OE,__,AE,__,SP,__,__,CB,__,__,DF,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,YB),
  /*I0*/ PT_(OK,OK,OK,__,OE,__,AE,__,SP,__,__,CB,__,__,DF,I0,I0,__,__,__,__,DE,__,__,__,__,__,__,__,__,DE,__,__,YB),
  /*R1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,R2,R2,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /*R2*/ PT_(OK,OK,OK,__,OE,__,AE,__,SP,__,__,CB,__,__,__,R2,R2,__,__,__,__,X1,__,__,__,__,__,__,__,__,X1,__,__,YB),
  /*X1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,X2,X2,__,X3,X3,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /*X2*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,X3,X3,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /*X3*/ PT_(OK,OK,OK,__,OE,__,AE,__,SP,__,__,__,__,__,__,X3,X3,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /****************************************************************************************************************/
  /*T1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,T2,__,__,__,__,__,__,__,__),
  /*T2*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,T3,__,__,__,__,__),
  /*T3*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,TR,__,__,__,__,__,__,__,__,__,__,__,__),
  /*F1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,F2,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /*F2*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,F3,__,__,__,__,__,__,__,__,__,__),
  /*F3*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,F4,__,__,__,__,__,__,__),
  /*F4*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,FA,__,__,__,__,__,__,__,__,__,__,__,__),
  /*N1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,N2,__,__,__,__,__),
  /*N2*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,N3,__,__,__,__,__,__,__,__,__,__),
  /*N3*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,NU,__,__,__,__,__,__,__,__,__,__),
  /****************************************************************************************************************/
  /*C1*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,C2,__),
  /*C2*/ PT_(C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C3,C2),
  /*C3*/ PT_(C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,CE,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C2,C3,C2),
  /*Y1*/ PT_(Y1,CE,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1,Y1),
  /*D1*/ PT_(__,__,__,__,__,__,__,__,__,__,D2,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__),
  /*D2*/ PT_(__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,U1,__,__,__,__,__),
  };
  #undef S
  #undef PT_

  /* map from (previous state+new character class) to the buffer policy. ignore=0/append=1/escape=2 */
  static const uint8_t buffer_policy_table[NR_STATES][NR_CLASSES] = {
  /*          white                                                                            ABCDF  other     */
  /*      sp nl  |  {  }  [  ]  :  ,  "  \  /  +  -  .  0  19 a  b  c  d  e  f  l  n  r  s  t  u  |  E  |  *  # */
  /*GO*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*OK*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*_O*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*_K*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*CO*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*_V*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*_A*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /**************************************************************************************************************/
  /*_S*/ { 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  /*E0*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0 },
  /*U1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  /*U2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  /*U3*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  /*U4*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  /**************************************************************************************************************/
  /*M0*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*Z0*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*I0*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  /*R1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*R2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  /*X1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*X2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*X3*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /**************************************************************************************************************/
  /*T1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*T2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*T3*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*F1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*F2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*F3*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*F4*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*N1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*N2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*N3*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /**************************************************************************************************************/
  /*C1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*C2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*C3*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*Y1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*D1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /*D2*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  };

  #define __ 0xff
  static const uint8_t utf8_header_table[256] =
  {
  /* 00 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 10 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 20 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 30 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 40 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 50 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 60 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 70 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 80 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 90 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* a0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* b0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* c0 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  /* d0 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  /* e0 */ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  /* f0 */ 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5,__,__,
  };

  static const uint8_t utf8_continuation_table[256] =
  {
  /*__0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 10 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 20 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 30 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 40 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 50 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 60 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 70 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* 80 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 90 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* a0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* b0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* c0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* d0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* e0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  /* f0 */__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
  };
  #undef __

  #define MODE_ARRAY 0
  #define MODE_OBJECT 1

  static const uint8_t hextable[] = {
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,255,255,255,255,255,255,
    255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  };

  #define hex(c) (hextable[(uint8_t) c])

  /* high surrogate range from d800 to dbff */
  /* low surrogate range dc00 to dfff */
  #define IS_HIGH_SURROGATE(uc) (((uc) & 0xfc00) == 0xd800)
  #define IS_LOW_SURROGATE(uc)  (((uc) & 0xfc00) == 0xdc00)

#endif
