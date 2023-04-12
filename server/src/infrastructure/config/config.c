/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. )
  +  Lucia Brando        (matr. )
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config.h"

/***************************************************************************
*                   CONFIGURATION STRUCTURE FUNCTIONS                      *
***************************************************************************/
config* provide_config(const char* file_name) {
  ini_parser* ini = init_parser(file_name); // Parse the given file

  config* cfg = malloc(sizeof(struct config));

  /* [Network] Retriving config options fields from the given config file */
  char* host    = (char*) get_value(ini, "network", "host");
  char* port    = (char*) get_value(ini, "network", "port");
  char* timeout = (char*) get_value(ini, "network", "timeout");

  /* [Connections] Retriving config options fields from the given config file */
  char* max_clients = (char*) get_value(ini, "connections", "max_clients");
  char* max_threads = (char*) get_value(ini, "connections", "max_threads");

  /* [Logging] Retriving config options fields from the given config file */
  char* log_level = (char*) get_value(ini, "logging", "log_level");
  char* log_file = (char*) get_value(ini, "logging", "log_file");

  /* Update the network setting accordingly with the config file or set a default value */
  cfg->ns.host = (host != NULL) ? host : "127.0.0.1";
  cfg->ns.port = (port != NULL) ? port : "8080";
  cfg->ns.timeout = (timeout != NULL) ? timeout : "0";

  /* Update the connection setting accordingly with the config file or set a default value */
  cfg->cs.max_clients = (max_clients != NULL) ? max_clients : "10";
  cfg->cs.max_threads = (max_threads != NULL) ? max_threads : "10";
  
  /* Update the logging setting accordingly with the config file or set a default value */
  cfg->ls.log_level = (log_level != NULL) ? log_level : "normal";
  cfg->ls.log_file = (log_file != NULL) ? log_file : "stderr";

  // Destroy the parser (no more needed)
  destroy_parser(ini);
  return cfg;
}

/***************************************************************************
*                     CONFIGURATION PARSER FUNCTIONS                       *
***************************************************************************/

// Helper function for string comparison
static int str_compare(const char*, const char*);

// Returns the next string in the split data taken from the parser
static char* next(ini_parser*, char*);

// Helper function for trimming
static void trim_back(ini_parser*, char*);

// Helper function used to discard lines
static char* discard_line(ini_parser*, char*);

static char *unescape_quoted_value(ini_parser*, char*);

/*
 * Helper function used to split data in place into string containing
 * section-headers, keys and values using 1 or more '\0' as delimeter
 * Unescape quoted values
*/
static void split_data(ini_parser*);

ini_parser* init_parser(const char* file_name) {
  ini_parser* parser = malloc(sizeof(struct ini_parser));
  int size;

  if (!parser) {
    fprintf(stderr, "[%s] (%s) Failed to allocated enought space for the ini parser", __FILE__, __func__);
    exit(EXIT_FAILURE);
  }

  memset(parser, 0, sizeof(struct ini_parser));

  /* Open the given file name */
  FILE* fp = fopen(file_name, "rb");
  if (!fp) {
    fprintf(stderr, "[%s] (%s) Failed to open the specified file <%s>", __FILE__, __func__, file_name);
    exit(EXIT_FAILURE);
  }

  // Get file size
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  // Rewind the file to the beggining of the STREAM
  rewind(fp);

  /* Load file content into memory, null terminate, init end var */
  parser->data = malloc(size + 1);
  parser->data[size] = '\0';
  parser->end = parser->data + size;
  int reader = fread(parser->data, 1, size, fp);

  if (reader != size) {
    fprintf(stderr, "[%s] (%s) Failed to read the specified file <%s>", __FILE__, __func__, file_name);
    exit(EXIT_FAILURE);
  }

  /* Prepare data after read it */
  split_data(parser);

  /* Close the give filename */
  fclose(fp);
  return parser;
}

void destroy_parser(ini_parser* p) {
  if (p->data)
    free(p->data);
  if (p)
    free(p);
}

static int str_compare(const char* _a, const char* _b) {
  for(;;) {
    int d = tolower(*_a) - tolower(*_b);
    if (d != 0 || !*_a) {
      return d;
    }
    _a++, _b++;
  }
}

static char* next(ini_parser* parser, char* v) {
  v += strlen(v);
  while(v < parser->end && *v == '\0')
    v++;

  return v;
}

static void trim_back(ini_parser* p, char* v) {
  while (v >= p->data && (*v == ' ' || *v == '\t' || *v == '\r')) {
    *v-- = '\0';
  }
}
static char* discard_line(ini_parser* p, char* v) {
  while(v < p->end && *v != '\n') {
    *v++ = '\0';
  }
  return v;
}
static char* unescape_quoted_value(ini_parser* p, char* v) {
  /* Use `q` as write-head and `p` as read-head, `p` is always ahead of `q`
   * as escape sequences are always larger than their resultant data */
  char* q = v;
  v++;
  while(v < p->end && *v != '"' && *v != '\r' && *v != '\n') {
    if (*v  == '\\') { // Handle escaped char
      p++;
      switch(*v) {
	default   : *q = *v;    break;
	case 'r'  : *q = '\r';  break;
	case 'n'  : *q = '\n';  break;
	case 't'  : *q = '\t';  break;
	case '\r' :
	case '\n' :
	case '\0' : return q;
      }
    } else { // Handle classic char
      *q = *v;
    }
    q++, p++;
  }
  return q;
}

static void split_data(ini_parser* parser) {
  char* start;
  char* line_start;
  char* data = parser->data;

  while (data < parser->end) {
    switch (*data) {

      case '\r':
      case '\n':
      case '\t':
      case ' ':
        *data = '\0';
        /* Fall through */

      case '\0':
        data++;
        break;

      case '[':
        data += strcspn(data, "]\n");
        *data = '\0';
        break;

      case ';':
        data = discard_line(parser, data);
        break;

      default:
        line_start = data;
        data += strcspn(data, "=\n");

        /* Is line missing a '='? */
        if (*data != '=') {
          data = discard_line(parser, line_start);
          break;
        }
        trim_back(parser, data - 1);

        /* Replace '=' and whitespace after it with '\0' */
        do {
          *data++ = '\0';
        } while (*data == ' ' || *data == '\r' || *data == '\t');

        /* Is a value after '=' missing? */
        if (*data == '\n' || *data == '\0') {
          data = discard_line(parser, line_start);
          break;
        }

        if (*data == '"') {
          /* Handle quoted string value */
          start = data;
          data = unescape_quoted_value(parser, data);

          /* Was the string empty? */
          if (data == start) {
            data = discard_line(parser, line_start);
            break;
          }

          /* Discard the rest of the line after the string value */
          data = discard_line(parser, data);

        } else {
          /* Handle normal value */
          data += strcspn(data, "\n");
          trim_back(parser, data - 1);
        }
        break;
    }
  }
}

const char* get_value(ini_parser* parser, const char* section, const char* key) {
  char* current_section = "";
  char* value;
  char* data = parser->data;

  if (*data == '\0') {
    data = next(parser, data);
  }

  while (data < parser->end) {
    if (*data == '[') {
      /* Handle section */
      current_section = data + 1;

    } else {
      /* Handle key */
      value = next(parser, data);
      if (!section || !str_compare(section, current_section)) {
	if (!str_compare(data, key)) {
	  return value;
	}
      }
      data = value;
    }

    data = next(parser, data);
  }
  return NULL;
}
