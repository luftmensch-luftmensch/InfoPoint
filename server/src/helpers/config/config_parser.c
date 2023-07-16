/*
  ╔═╗  ╔═╗  ╔╗╔  ╔═╗  ╦  ╔═╗      ╔═╗  ╔═╗  ╦═╗  ╔═╗  ╔═╗  ╦═╗
  ║    ║ ║  ║║║  ╠╣   ║  ║ ╦      ╠═╝  ╠═╣  ╠╦╝  ╚═╗  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╝╚╝  ╚    ╩  ╚═╝      ╩    ╩ ╩  ╩╚═  ╚═╝  ╚═╝  ╩╚═
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "config_parser.h"

/***************************************************************************
*                        INTERNAL SUPPORTS FUNCTIONS                       *
***************************************************************************/

/* Returns the requested section. */
static config_status get_config_section(const config_parser*, const char*, config_section**);

/* Returns the pair of <key,value> from a given parser */
static config_status get_key_value_pair(config_section*, const char*, config_key_val**);

/* Insert the specified section in the given parser */
static config_status add_section_to_cfg(config_parser*, const char*, config_section**);

/* Retrieve section name from a given buffer */
static config_status get_section_name(config_parser*, char*, char**);

/* Retrieve <key,value> pair from a given buffer */
static config_status retrieve_key_value_pair(config_parser*, char*, char**, char**);

static config_status get_config_section(const config_parser *cfg, const char *section, config_section **sect) {
  if (!cfg || !sect)
    return CONFIG_ERR_INVALID_PARAM;

  TAILQ_FOREACH(*sect, &cfg->sect_list, next) {
    if ( (section && (*sect)->name && !strcmp((*sect)->name, section)) ||
	 (!section && !(*sect)->name) ) {
      return CONFIG_OK;
    }
  }

  return CONFIG_ERR_NO_SECTION;
}

static config_status get_key_value_pair(config_section *sect, const char *key, config_key_val **kv) {
  if (!sect || !key || !kv)
    return CONFIG_ERR_INVALID_PARAM;

  TAILQ_FOREACH(*kv, &sect->kv_list, next) {
    if (!strcmp((*kv)->key, key))
      return CONFIG_OK;
  }

  return CONFIG_ERR_NO_KEY;
}

config_status read_str_from_cfg(const config_parser* cfg, const char* section, const char* key, char* value, int size, const char* default_value) {
  config_section *sect = NULL;
  config_key_val *kv   = NULL;
  config_status ret  = CONFIG_OK;

  if (!cfg || !key || !value || (size < 1))
    return CONFIG_ERR_INVALID_PARAM;

  *value = '\0';

  if (((ret = get_config_section(cfg, section, &sect)) != CONFIG_OK) ||
      ((ret = get_key_value_pair(sect, key, &kv)) != CONFIG_OK) ) {
    if (default_value) {
      memcpy((void*) value, (void*) default_value, (strlen(default_value) + 1));
    }
    return ret;
  }

  memcpy((void*) value, (void*) kv->value, (strlen(kv->value) + 1));
  return CONFIG_OK;
}

config_status read_uint_from_cfg(const config_parser *cfg, const char *section, const char *key, unsigned int *value, unsigned int dfl_value) {
  config_section  *sect = NULL;
  config_key_val *kv   = NULL;
  config_status  ret  = CONFIG_OK;
  char           *p    = NULL;

  if (!cfg || !key || !value)
    return CONFIG_ERR_INVALID_PARAM;

  *value = dfl_value;

  if ( ((ret = get_config_section(cfg, section, &sect)) != CONFIG_OK) ||
       ((ret = get_key_value_pair(sect, key, &kv)) != CONFIG_OK) ) {
    return ret;
  }

  *value = (unsigned int) strtoul(kv->value, &p, 10);
  if (*p || (errno == ERANGE))
    return CONFIG_ERR_INVALID_VALUE;

  return CONFIG_OK;
}

static config_status add_section_to_cfg(config_parser *cfg, const char *section, config_section **sect) {
  config_section *_sect = NULL;
  config_status  ret   = CONFIG_OK;

  if (!cfg)
    return CONFIG_ERR_INVALID_PARAM;

  if (!sect)
    sect = &_sect;

  if ((ret = get_config_section(cfg, section, sect)) != CONFIG_ERR_NO_SECTION)
    return ret;

  *sect = calloc(1, sizeof(config_section));
  if (*sect == NULL)
    return CONFIG_ERR_MEMALLOC;

  if (section) {
    if (((*sect)->name = strdup(section)) == NULL) {
      free(*sect);
      return CONFIG_ERR_MEMALLOC;
    }
  }

  TAILQ_INIT(&(*sect)->kv_list);
  TAILQ_INSERT_TAIL(&cfg->sect_list, *sect, next);
  ++(cfg->numofsect);

  return CONFIG_OK;
}

config_status add_str_to_cfg(config_parser *cfg, const char *section, const char *key, const char *value) {
  config_section  *sect = NULL;
  config_key_val *kv   = NULL;
  config_status ret  = CONFIG_OK;
  const char     *p    = NULL;
  const char     *q    = NULL;

  if (!cfg || !key || !value)
    return CONFIG_ERR_INVALID_PARAM;

  if ((ret = add_section_to_cfg(cfg, section, &sect)) != CONFIG_OK)
    return ret;

  switch (ret = get_key_value_pair(sect, key, &kv)) {
  case CONFIG_OK:
    if (kv->value) {
      free(kv->value);
      kv->value = NULL;
    }
    break;

  case CONFIG_ERR_NO_KEY:
    if ((kv = calloc(1, sizeof(config_key_val))) == NULL)
      return CONFIG_ERR_MEMALLOC;
    if ((kv->key = strdup(key)) == NULL) {
      free(kv);
      return CONFIG_ERR_MEMALLOC;
    }
    TAILQ_INSERT_TAIL(&sect->kv_list, kv, next);
    ++(sect->numofkv);
    break;

  default:
    return ret;
  }

  for (p = value; *p && isspace(*p); ++p)
    ;
  for (q = p; *q && (*q != '\r') && (*q != '\n') && !strchr(cfg->comment_chars, *q); ++q)
    ;
  while (*q && (q > p) && isspace(*(q - 1)))
    --q;

  kv->value = (char *) malloc(q - p + 1);
  if (kv->value == NULL) {
    TAILQ_REMOVE(&sect->kv_list, kv, next);
    --(sect->numofkv);
    free(kv->key);
    free(kv);
    return CONFIG_ERR_MEMALLOC;
  }
  memcpy(kv->value, p, q - p);
  kv->value[q - p] = '\0';

  return CONFIG_OK;
}


config_status add_uint_to_cfg(config_parser *cfg, const char *section, const char *key, unsigned int value) {
  char buf[64];

  snprintf(buf, sizeof(buf), "%u", value);

  return add_str_to_cfg(cfg, section, key, buf);
}

static void remove_key_val_from_section(config_section *sect, config_key_val *kv) {
  TAILQ_REMOVE(&sect->kv_list, kv, next);
  --(sect->numofkv);

  if (kv->key)
    free(kv->key);
  if (kv->value)
    free(kv->value);
  free(kv);
}


static void remove_section_from_cfg(config_parser *cfg, config_section *sect) {
  config_key_val *kv, *t_kv;

  if (!cfg || !sect)
    return;

  TAILQ_REMOVE(&cfg->sect_list, sect, next);
  --(cfg->numofsect);

  TAILQ_FOREACH_SAFE(kv, &sect->kv_list, next, t_kv) {
    remove_key_val_from_section(sect, kv);
  }

  if (sect->name)
    free(sect->name);
  free(sect);
}

config_parser* init_config() {
  config_parser *cfg = NULL;

  cfg = calloc(1, sizeof(config_parser));
  if (cfg == NULL)
    return NULL;

  TAILQ_INIT(&cfg->sect_list);

  /* add default section */
  if (add_section_to_cfg(cfg, CONFIG_SECTION_FLAT, NULL) != CONFIG_OK) {
    free(cfg);
    return NULL;
  }

  /* Config parser field initialization */
  cfg->comment_chars = strdup(COMMENT_CHARS);
  cfg->keyval_sep = KEYVAL_SEP;
  cfg->true_str = strdup(STR_TRUE);
  cfg->false_str = strdup(STR_FALSE);
  cfg->initnum = CONFIG_INIT_MAGIC;

  return cfg;
}

void destroy_config(config_parser *cfg) {
  config_section *sect, *t_sect;

  if (cfg == NULL)
    return;

  TAILQ_FOREACH_SAFE(sect, &cfg->sect_list, next, t_sect) {
    remove_section_from_cfg(cfg, sect);
  }

  if (cfg->comment_chars) free(cfg->comment_chars);
  if (cfg->true_str)      free(cfg->true_str);
  if (cfg->false_str)     free(cfg->false_str);

  free(cfg);
}

static config_status get_section_name(config_parser *cfg, char* buffer, char **section) {
  char *q, *r;

  if (!cfg || !buffer || !*buffer || !section)
    return CONFIG_ERR_INVALID_PARAM;

  *section = NULL;

  /* get section name */
  while (*buffer && isspace(*buffer))
    ++buffer;

  if (*buffer != '[')
    return CONFIG_ERR_PARSING;

  ++buffer;
  while (*buffer && isspace(*buffer))
    ++buffer;

  for (q = buffer;
       *q && (*q != '\r') && (*q != '\n') && (*q != ']') && !strchr(cfg->comment_chars, *q);
       ++q)
    ;

  if (*q != ']')
    return CONFIG_ERR_PARSING;

  r = q + 1;

  while (*q && (q > buffer) && isspace(*(q - 1)))
    --q;

  if (q == buffer) /* section has no name */
    return CONFIG_ERR_PARSING;

  *q = '\0';
  *section = buffer;

  /* check rest of section */
  while (*r && isspace(*r))
    ++r;

  /* there are unrecognized trailing data */
  if (*r && !strchr(cfg->comment_chars, *r))
    return CONFIG_ERR_PARSING;

  return CONFIG_OK;
}

static config_status retrieve_key_value_pair(config_parser *cfg, char *p, char **key, char **val) {
  char *q, *v;

  if (!cfg || !p || !*p || !key || !val)
    return CONFIG_ERR_INVALID_PARAM;

  *key = *val = NULL;

  /* get key */
  while (*p && isspace(*p))
    ++p;

  for (q = p;
       *q && (*q != '\r') && (*q != '\n') && (*q != cfg->keyval_sep) && !strchr(cfg->comment_chars, *q);
       ++q)
    ;

  if (*q != cfg->keyval_sep)
    return CONFIG_ERR_PARSING;

  v = q + 1;

  while (*q && (q > p) && isspace(*(q - 1)))
    --q;

  if (q == p) /* no key name */
    return CONFIG_ERR_PARSING;

  *q = '\0';
  *key = p;

  /* get value */
  while (*v && isspace(*v))
    ++v;

  for (q = v;
       *q && (*q != '\r') && (*q != '\n') && !strchr(cfg->comment_chars, *q);
       ++q)
    ;

  while (*q && (q > v) && isspace(*(q - 1)))
    --q;

  if (q == v) /* no value */
    return CONFIG_ERR_INVALID_VALUE;

  *q = '\0';
  *val = v;

  return CONFIG_OK;
}

config_status read_config(FILE* fp, config_parser** cfg) {
  config_section* section = NULL;
  char *p = NULL;
  char* curr_section = NULL;
  char* key = NULL;
  char* val = NULL;
  char buf[4096];
  config_parser* _cfg = NULL;
  bool newcfg = false;
  config_status  status  = CONFIG_OK;

  if ( !fp || !cfg || (*cfg && ((*cfg)->initnum != CONFIG_INIT_MAGIC)) )
    return CONFIG_ERR_INVALID_PARAM;

  if (*cfg == NULL) {
    _cfg = init_config();
    if (_cfg == NULL)
      return CONFIG_ERR_MEMALLOC;
    *cfg = _cfg;
    newcfg = true;
  }
  else
    _cfg = *cfg;

  while (!feof(fp)) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      continue;

    for (p = buf; *p && isspace(*p) ; ++p)
      ;
    if (!*p || strchr(_cfg->comment_chars, *p))
      continue;

    if (*p == '[') {
      if ((status = get_section_name(_cfg, p, &curr_section)) != CONFIG_OK){

	if (newcfg) {
	  destroy_config(_cfg);
	  *cfg = NULL;
	}

	return status;
	
      }

      if ((status = add_section_to_cfg(_cfg, curr_section, &section)) != CONFIG_OK) {
	

	if (newcfg) {
	  destroy_config(_cfg);
	  *cfg = NULL;
	}

	return status;
      }
    }
    else {
      if ((status = retrieve_key_value_pair(_cfg, p, &key, &val)) != CONFIG_OK) {
	
	if (newcfg) {
	  destroy_config(_cfg);
	  *cfg = NULL;
	}
	return status;
      }

      if ((status = add_str_to_cfg(_cfg, section->name, key, val)) != CONFIG_OK) {
	if (newcfg) {
	  destroy_config(_cfg);
	  *cfg = NULL;
	}
	return status;
      }
    }
  }

  return CONFIG_OK;
}

config_status read_file(const char *filename, config_parser **cfg) {
  FILE      *fp  = NULL;
  config_status  ret = CONFIG_OK;

  if ( !filename || !cfg || (*cfg && ((*cfg)->initnum != CONFIG_INIT_MAGIC)) )
    return CONFIG_ERR_INVALID_PARAM;

  if ((fp = fopen(filename, "r")) == NULL)
    return CONFIG_ERR_FILE;

  ret = read_config(fp, cfg);

  fclose(fp);

  return ret;
}
