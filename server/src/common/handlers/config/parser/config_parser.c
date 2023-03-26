/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗      ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╔═╗  ╦═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦      ╠═╝  ╠═╣  ╠╦╝  ╚═╗  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝      ╩    ╩ ╩  ╩╚═  ╚═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "config_parser.h"
#include "config_types.h"


static inline void *memory_realloc(void *(*realloc_fct)(void *, size_t), void *ptr, size_t size) {
	return (realloc_fct) ? realloc_fct(ptr, size) : realloc(ptr, size);
}

static inline void *memory_calloc(void *(*calloc_fct)(size_t, size_t), size_t nmemb, size_t size) {
	return (calloc_fct) ? calloc_fct(nmemb, size) : calloc(nmemb, size);
}

#define parser_calloc(parser, n, s) memory_calloc(parser->config.u_calloc, n, s)
#define parser_realloc(parser, n, s) memory_realloc(parser->config.u_realloc, n, s)

static int state_grow(parser* p) {
  uint32_t new_size = p->stack_size * 2;
  void* ptr;
  if (p->config.max_nesting != 0)
    return JSON_ERROR_NESTING_LIMIT;

  ptr = parser_realloc(p, p->stack, new_size * (sizeof(uint8_t)));
  if (!ptr)
    return JSON_ERROR_NO_MEMORY;
  p->stack = ptr;
  p->stack_size = new_size;
  return 0;
}

static int state_push(parser *parser, int mode) {
  if (parser->stack_offset >= parser->stack_size) {
    int ret = state_grow(parser);
    if (ret)
      return ret;
  }
  parser->stack[parser->stack_offset++] = mode;
  return 0;
}

static int state_pop(parser *parser, int mode) {
  if (parser->stack_offset == 0)
    return JSON_ERROR_POP_EMPTY;
  parser->stack_offset--;
  if (parser->stack[parser->stack_offset] != mode)
    return JSON_ERROR_POP_UNEXPECTED_MODE;
  return 0;
}

static int buffer_grow(parser *parser) {
  uint32_t newsize;
  void *ptr;
  uint32_t max = parser->config.max_data;

  if (max > 0 && parser->buffer_size == max)
    return JSON_ERROR_DATA_LIMIT;
  newsize = parser->buffer_size * 2;
  if (max > 0 && newsize > max)
    newsize = max;

  ptr = parser_realloc(parser, parser->buffer, newsize * sizeof(char));
  if (!ptr)
    return JSON_ERROR_NO_MEMORY;
  parser->buffer = ptr;
  parser->buffer_size = newsize;
  return 0;
}

static int buffer_push(parser *parser, unsigned char c) {
  int ret;

  if (parser->buffer_offset + 1 >= parser->buffer_size) {
    ret = buffer_grow(parser);
    if (ret)
      return ret;
  }
  parser->buffer[parser->buffer_offset++] = c;
  return 0;
}

static int do_callback_withbuf(parser *parser, int type) {
  if (!parser->callback)
    return 0;
  parser->buffer[parser->buffer_offset] = '\0';
  return (*parser->callback)(parser->userdata, type, parser->buffer, parser->buffer_offset);
}

static int do_callback(parser *parser, int type) {
  if (!parser->callback)
    return 0;
  return (*parser->callback)(parser->userdata, type, NULL, 0);
}

static int do_buffer(parser *parser) {
  int ret = 0;

  switch (parser->type) {
  case JSON_KEY: case JSON_STRING:
  case JSON_FLOAT: case JSON_INT:
  case JSON_NULL: case JSON_TRUE: case JSON_FALSE:
    ret = do_callback_withbuf(parser, parser->type);
    if (ret)
      return ret;
    break;
  default:
    break;
  }
  parser->buffer_offset = 0;
  return ret;
}

/* transform an unicode [0-9A-Fa-f]{4} sequence into a proper value */
static int decode_unicode_char(parser* parser) {
  uint32_t uval;
  char *b = parser->buffer;
  int offset = parser->buffer_offset;

  uval = (hex(b[offset - 4]) << 12) | (hex(b[offset - 3]) << 8)
    | (hex(b[offset - 2]) << 4) | hex(b[offset - 1]);

  parser->buffer_offset -= 4;

  /* fast case */
  if (!parser->unicode_multi && uval < 0x80) {
    b[parser->buffer_offset++] = (char) uval;
    return 0;
  }

  if (parser->unicode_multi) {
    if (!IS_LOW_SURROGATE(uval))
      return JSON_ERROR_UNICODE_MISSING_LOW_SURROGATE;

    uval = 0x10000 + ((parser->unicode_multi & 0x3ff) << 10) + (uval & 0x3ff);
    b[parser->buffer_offset++] = (char) ((uval >> 18) | 0xf0);
    b[parser->buffer_offset++] = (char) (((uval >> 12) & 0x3f) | 0x80);
    b[parser->buffer_offset++] = (char) (((uval >> 6) & 0x3f) | 0x80);
    b[parser->buffer_offset++] = (char) ((uval & 0x3f) | 0x80);
    parser->unicode_multi = 0;
    return 0;
  }

  if (IS_LOW_SURROGATE(uval))
    return JSON_ERROR_UNICODE_UNEXPECTED_LOW_SURROGATE;
  if (IS_HIGH_SURROGATE(uval)) {
    parser->unicode_multi = uval;
    return 0;
  }

  if (uval < 0x800) {
    b[parser->buffer_offset++] = (char) ((uval >> 6) | 0xc0);
    b[parser->buffer_offset++] = (char) ((uval & 0x3f) | 0x80);
  } else {
    b[parser->buffer_offset++] = (char) ((uval >> 12) | 0xe0);
    b[parser->buffer_offset++] = (char) (((uval >> 6) & 0x3f) | 0x80);
    b[parser->buffer_offset++] = (char) (((uval >> 0) & 0x3f) | 0x80);
  }
  return 0;
}

static int buffer_push_escape(parser* parser, unsigned char next) {
  char c = '\0';

  switch (next) {
  case 'b': c = '\b'; break;
  case 'f': c = '\f'; break;
  case 'n': c = '\n'; break;
  case 'r': c = '\r'; break;
  case 't': c = '\t'; break;
  case '"': c = '"'; break;
  case '/': c = '/'; break;
  case '\\': c = '\\'; break;
  }
  /* push the escaped character */
  return buffer_push(parser, c);
}


static int act_uc(parser* parser) {
  int ret;
  CHK(decode_unicode_char(parser));
  parser->state = (parser->unicode_multi) ? STATE_D1 : STATE__S;
  return 0;
}

static int act_yb(parser *parser) {
  if (!parser->config.allow_yaml_comments)
    return JSON_ERROR_COMMENT_NOT_ALLOWED;
  parser->save_state = parser->state;
  return 0;
}

static int act_cb(parser *parser) {
  if (!parser->config.allow_c_comments)
    return JSON_ERROR_COMMENT_NOT_ALLOWED;
  parser->save_state = parser->state;
  return 0;
}

static int act_ce(parser* parser) {
  parser->state = (parser->save_state > STATE__A) ? STATE_OK : parser->save_state;
  return 0;
}

static int act_ob(parser* parser) {
  int ret;
  CHK(do_callback(parser, JSON_OBJECT_BEGIN));
  CHK(state_push(parser, MODE_OBJECT));
  parser->expecting_key = 1;
  return 0;
}

static int act_oe(parser* parser) {
  int ret;
  CHK(state_pop(parser, MODE_OBJECT));
  CHK(do_callback(parser, JSON_OBJECT_END));
  parser->expecting_key = 0;
  return 0;
}

static int act_ab(parser* parser) {
  int ret;
  CHK(do_callback(parser, JSON_ARRAY_BEGIN));
  CHK(state_push(parser, MODE_ARRAY));
  return 0;
}

static int act_ae(parser* parser) {
  int ret;
  CHK(state_pop(parser, MODE_ARRAY));
  CHK(do_callback(parser, JSON_ARRAY_END));
  return 0;
}

static int act_se(parser* parser) {
  int ret;
  CHK(do_callback_withbuf(parser, (parser->expecting_key) ? JSON_KEY : JSON_STRING));
  parser->buffer_offset = 0;
  parser->state = (parser->expecting_key) ? STATE_CO : STATE_OK;
  parser->expecting_key = 0;
  return 0;
}

static int act_sp(parser* parser) {
  if (parser->stack_offset == 0)
    return JSON_ERROR_COMMA_OUT_OF_STRUCTURE;
  if (parser->stack[parser->stack_offset - 1] == MODE_OBJECT) {
    parser->expecting_key = 1;
    parser->state = STATE__K;
  } else
    parser->state = STATE__V;
  return 0;
}

struct action_descr {
  int (*call)(parser *parser);
  uint8_t type;
  uint8_t state; /* 0 if we let the callback set the value it want */
  uint8_t dobuffer;
};

static struct action_descr actions_map[] = {
  { NULL,   JSON_NONE,  STATE__V, 0 }, /* KS */
  { act_sp, JSON_NONE,  0,        1 }, /* SP */
  { act_ab, JSON_NONE,  STATE__A, 0 }, /* AB */
  { act_ae, JSON_NONE,  STATE_OK, 1 }, /* AE */
  { act_ob, JSON_NONE,  STATE__O, 0 }, /* OB */
  { act_oe, JSON_NONE,  STATE_OK, 1 }, /* OE */
  { act_cb, JSON_NONE,  STATE_C1, 1 }, /* CB */
  { act_yb, JSON_NONE,  STATE_Y1, 1 }, /* YB */
  { act_ce, JSON_NONE,  0,        0 }, /* CE */
  { NULL,   JSON_FALSE, STATE_OK, 0 }, /* FA */
  { NULL,   JSON_TRUE,  STATE_OK, 0 }, /* TR */
  { NULL,   JSON_NULL,  STATE_OK, 0 }, /* NU */
  { NULL,   JSON_FLOAT, STATE_X1, 0 }, /* DE */
  { NULL,   JSON_FLOAT, STATE_R1, 0 }, /* DF */
  { act_se, JSON_NONE,  0,        0 }, /* SE */
  { NULL,   JSON_INT,   STATE_M0, 0 }, /* MX */
  { NULL,   JSON_INT,   STATE_Z0, 0 }, /* ZX */
  { NULL,   JSON_INT,   STATE_I0, 0 }, /* IX */
  { act_uc, JSON_NONE,  0,        0 }, /* UC */
};

static int do_action(parser* parser, int next_state) {
  struct action_descr *descr = &actions_map[next_state & ~0x80];

  if (descr->call) {
    int ret;
    if (descr->dobuffer)
      CHK(do_buffer(parser));
    CHK((descr->call)(parser));
  }
  if (descr->state)
    parser->state = descr->state;
  parser->type = descr->type;
  return 0;
}

/** json_parser_init initialize a parser structure taking a config,
 * a config and its userdata.
 * return JSON_ERROR_NO_MEMORY if memory allocation failed or SUCCESS.
 */
int init_parser(parser *parser, json_config *config, parser_callback callback, void *userdata) {
  memset(parser, 0, sizeof(*parser));

  if (config)
    memcpy(&parser->config, config, sizeof(json_config));
  parser->callback = callback;
  parser->userdata = userdata;

  /* initialise parsing stack and state */
  parser->stack_offset = 0;
  parser->state = STATE_GO;

  /* initialize the parse stack */
  parser->stack_size = (parser->config.max_nesting > 0)
    ? parser->config.max_nesting
    : PARSER_DEFAULT_STACK_SIZE;

  parser->stack = parser_calloc(parser, parser->stack_size, sizeof(parser->stack[0]));
  if (!parser->stack)
    return JSON_ERROR_NO_MEMORY;

  /* initialize the parse buffer */
  parser->buffer_size = (parser->config.buffer_initial_size > 0)
    ? parser->config.buffer_initial_size
    : PARSER_DEFAULT_BUFFER_SIZE;

  if (parser->config.max_data > 0 && parser->buffer_size > parser->config.max_data)
    parser->buffer_size = parser->config.max_data;

  parser->buffer = parser_calloc(parser, parser->buffer_size, sizeof(char));
  if (!parser->buffer) {
    free(parser->stack);
    return JSON_ERROR_NO_MEMORY;
  }
  return 0;
}

int destroy_parser(parser *parser) {
  if (!parser)
    return 0;
  free(parser->stack);
  free(parser->buffer);
  parser->stack = NULL;
  parser->buffer = NULL;
  return 0;
}

/** json_parser_is_done return 0 is the parser isn't in a finish state. !0 if it is */
int parser_is_done(parser *parser) {
  /* need to compare the state to !GO to not accept empty document */
  return parser->stack_offset == 0 && parser->state != STATE_GO;
}

/** json_parser_string append a string s with a specific length to the parser
 * return 0 if everything went ok, a JSON_ERROR_* otherwise.
 * the user can supplied a valid processed pointer that will
 * be fill with the number of processed characters before returning */
int parse_string(parser* parser, const char* s, uint32_t length, uint32_t* processed) {
  int ret;
  int next_class, next_state;
  int buffer_policy;
  uint32_t i;

  ret = 0;
  for (i = 0; i < length; i++) {
    unsigned char ch = s[i];

    ret = 0;
    if (parser->utf8_multibyte_left > 0) {
      if (utf8_continuation_table[ch] != 0) {
	ret = JSON_ERROR_UTF8;
	break;
      }
      next_class = C_OTHER;
      parser->utf8_multibyte_left--;
    } else {
      parser->utf8_multibyte_left = utf8_header_table[ch];
      if (parser->utf8_multibyte_left == 0xff) {
	ret = JSON_ERROR_UTF8;
	break;
      }
      next_class = (parser->utf8_multibyte_left > 0) ? C_OTHER : character_class[ch];
      if (next_class == C_ERROR) {
	ret = JSON_ERROR_BAD_CHAR;
	break;
      }
    }

    next_state = state_transition_table[parser->state][next_class];
    buffer_policy = buffer_policy_table[parser->state][next_class];
    //fprintf(stderr, "addchar %d (current-state=%d, next-state=%d, buf-policy=%d)\n", ch, parser->state, next_state, buffer_policy);
    if (next_state == STATE___) {
      ret = JSON_ERROR_UNEXPECTED_CHAR;
      break;
    }

    /* add char to buffer */
    if (buffer_policy) {
      ret = (buffer_policy == 2)
	? buffer_push_escape(parser, ch)
	: buffer_push(parser, ch);
      if (ret)
	break;
    }

    /* move to the next level */
    if (IS_STATE_ACTION(next_state))
      ret = do_action(parser, next_state);
    else
      parser->state = next_state;
    if (ret)
      break;
  }
  if (processed)
    *processed = i;
  return ret;
}

/** json_parser_char append one single char to the parser
 * return 0 if everything went ok, a JSON_ERROR_* otherwise */
int parse_char(parser* parser, unsigned char ch) {
  return parse_string(parser, (char *) &ch, 1, NULL);
}

int init_printer(printer* printer, printer_callback callback, void *userdata) {
  memset(printer, '\0', sizeof(*printer));
  printer->callback = callback;
  printer->userdata = userdata;

  printer->indentstr = "\t";
  printer->indentlevel = 0;
  printer->enter_object = 1;
  printer->first = 1;
  return 0;
}

/** json_print_free free a printer context
 * doesn't do anything now, but in future print_init could allocate memory */
int destroy_printer(printer *printer) {
  memset(printer, '\0', sizeof(*printer));
  return 0;
}

/* escape a C string to be a JSON valid string on the wire.
 * XXX: it doesn't do unicode verification. yet?. */
static int print_string(printer *printer, const char *data, uint32_t length) {
  uint32_t i;

  printer->callback(printer->userdata, "\"", 1);
  for (i = 0; i < length; i++) {
    unsigned char c = data[i];
    if (c < 36) {
      char const *esc = character_escape[c];
      printer->callback(printer->userdata, esc, strlen(esc));
    } else if (c == '\\') {
      printer->callback(printer->userdata, "\\\\", 2);
    } else
      printer->callback(printer->userdata, data + i, 1);
  }
  printer->callback(printer->userdata, "\"", 1);
  return 0;
}

static int print_binary_string(printer *printer, const char *data, uint32_t length) {
  uint32_t i;

  printer->callback(printer->userdata, "\"", 1);
  for (i = 0; i < length; i++) {
    unsigned char c = data[i];
    char const *esc = character_escape[c];
    printer->callback(printer->userdata, esc, strlen(esc));
  }
  printer->callback(printer->userdata, "\"", 1);
  return 0;
}


static int print_indent(printer *printer) {
  int i;
  printer->callback(printer->userdata, "\n", 1);
  for (i = 0; i < printer->indentlevel; i++)
    printer->callback(printer->userdata, printer->indentstr, strlen(printer->indentstr));
  return 0;
}

static int json_print_mode(printer *printer, int type, const char *data, uint32_t length, int pretty) {
  int enterobj = printer->enter_object;

  if (!enterobj && !printer->afterkey && (type != JSON_ARRAY_END && type != JSON_OBJECT_END)) {
    printer->callback(printer->userdata, ",", 1);
    if (pretty) print_indent(printer);
  }

  if (pretty && (enterobj && !printer->first && (type != JSON_ARRAY_END && type != JSON_OBJECT_END))) {
    print_indent(printer);
  }

  printer->first = 0;
  printer->enter_object = 0;
  printer->afterkey = 0;
  switch (type) {
  case JSON_ARRAY_BEGIN:
    printer->callback(printer->userdata, "[", 1);
    printer->indentlevel++;
    printer->enter_object = 1;
    break;
  case JSON_OBJECT_BEGIN:
    printer->callback(printer->userdata, "{", 1);
    printer->indentlevel++;
    printer->enter_object = 1;
    break;
  case JSON_ARRAY_END:
  case JSON_OBJECT_END:
    printer->indentlevel--;
    if (pretty && !enterobj) print_indent(printer);
    printer->callback(printer->userdata, (type == JSON_OBJECT_END) ? "}" : "]", 1);
    break;
  case JSON_INT: printer->callback(printer->userdata, data, length); break;
  case JSON_FLOAT: printer->callback(printer->userdata, data, length); break;
  case JSON_NULL: printer->callback(printer->userdata, "null", 4); break;
  case JSON_TRUE: printer->callback(printer->userdata, "true", 4); break;
  case JSON_FALSE: printer->callback(printer->userdata, "false", 5); break;
  case JSON_KEY:
    print_string(printer, data, length);
    printer->callback(printer->userdata, ": ", (pretty) ? 2 : 1);
    printer->afterkey = 1;
    break;
  case JSON_STRING:
    print_string(printer, data, length);
    break;
  case JSON_BSTRING:
    print_binary_string(printer, data, length);
    break;
  default:
    break;
  }

  return 0;
}

/** json_print_pretty pretty print the passed argument (type/data/length). */
int printer_pretty(printer* printer, int type, const char *data, uint32_t length) {
  return json_print_mode(printer, type, data, length, 1);
}

/** json_print_raw prints without eye candy the passed argument (type/data/length). */
int json_print_raw(printer* printer, int type, const char *data, uint32_t length) {
  return json_print_mode(printer, type, data, length, 0);
}

/** json_print_args takes multiple types and pass them to the printer function */
int json_print_args(printer *printer,
		    int (*f)(struct printer*, int, const char *, uint32_t),
		    ...) {
  va_list ap;
  char *data;
  uint32_t length;
  int type, ret;

  ret = 0;
  va_start(ap, f);
  while ((type = va_arg(ap, int)) != -1) {
    switch (type) {
    case JSON_ARRAY_BEGIN:
    case JSON_ARRAY_END:
    case JSON_OBJECT_BEGIN:
    case JSON_OBJECT_END:
    case JSON_NULL:
    case JSON_TRUE:
    case JSON_FALSE:
      ret = (*f)(printer, type, NULL, 0);
      break;
    case JSON_INT:
    case JSON_FLOAT:
    case JSON_KEY:
    case JSON_STRING:
      data = va_arg(ap, char *);
      length = va_arg(ap, uint32_t);
      if (length == -1)
	length = strlen(data);
      ret = (*f)(printer, type, data, length);
      break;
    }
    if (ret)
      break;
  }
  va_end(ap);
  return ret;
}

static int dom_push(struct dom* ctx, void *val) {
  if (ctx->stack_offset == ctx->stack_size) {
    void *ptr;
    uint32_t newsize = ctx->stack_size * 2;
    ptr = memory_realloc(ctx->user_realloc, ctx->stack, newsize);
    if (!ptr)
      return JSON_ERROR_NO_MEMORY;
    ctx->stack = ptr;
    ctx->stack_size = newsize;
  }
  ctx->stack[ctx->stack_offset].val = val;
  ctx->stack[ctx->stack_offset].key = NULL;
  ctx->stack[ctx->stack_offset].key_length = 0;
  ctx->stack_offset++;
  return 0;
}

static int dom_pop(struct dom *ctx, void **val) {
  ctx->stack_offset--;
  *val = ctx->stack[ctx->stack_offset].val;
  return 0;
}

int init_dom(dom *dom, dom_create_structure create_structure, dom_create_data create_data, dom_append append) {
  memset(dom, 0, sizeof(*dom));
  dom->stack_size = 1024;
  dom->stack_offset = 0;
  dom->stack = memory_calloc(dom->user_calloc, dom->stack_size, sizeof(*(dom->stack)));
  if (!dom->stack)
    return JSON_ERROR_NO_MEMORY;
  dom->append = append;
  dom->create_structure = create_structure;
  dom->create_data = create_data;
  return 0;
}

int destroy_dom(dom *dom) {
  free(dom->stack);
  return 0;
}

int dom_callback(void *userdata, int type, const char *data, uint32_t length) {
  struct dom *ctx = userdata;
  void *v;
  struct stack_elem *stack = NULL;

  switch (type) {
  case JSON_ARRAY_BEGIN:
  case JSON_OBJECT_BEGIN:
    v = ctx->create_structure(ctx->stack_offset, type == JSON_OBJECT_BEGIN);
    if (!v)
      return JSON_ERROR_CALLBACK;
    dom_push(ctx, v);
    break;
  case JSON_OBJECT_END:
  case JSON_ARRAY_END:
    dom_pop(ctx, &v);
    if (ctx->stack_offset > 0) {
      stack = &(ctx->stack[ctx->stack_offset - 1]);
      ctx->append(stack->val, stack->key, stack->key_length, v);
      free(stack->key);
    } else
      ctx->root_structure = v;
    break;
  case JSON_KEY:
    stack = &(ctx->stack[ctx->stack_offset - 1]);
    stack->key = memory_calloc(ctx->user_calloc, length + 1, sizeof(char));
    stack->key_length = length;
    if (!stack->key)
      return JSON_ERROR_NO_MEMORY;
    memcpy(stack->key, data, length);
    break;
  case JSON_STRING:
  case JSON_INT:
  case JSON_FLOAT:
  case JSON_NULL:
  case JSON_TRUE:
  case JSON_FALSE:
    stack = &(ctx->stack[ctx->stack_offset - 1]);
    v = ctx->create_data(type, data, length);
    if (!v)
      return JSON_ERROR_CALLBACK;
    if (ctx->append(stack->val, stack->key, stack->key_length, v))
      return JSON_ERROR_CALLBACK;
    free(stack->key);
    break;
  }
  return 0;
}
