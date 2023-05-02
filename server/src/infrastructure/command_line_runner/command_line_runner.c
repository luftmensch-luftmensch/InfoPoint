/*
  ╔═╗  ╔═╗  ╔╦╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗        ╦    ╦  ╔╗╔  ╔═╗        ╦═╗  ╦ ╦  ╔╗╔  ╔╗╔  ╔═╗  ╦═╗
  ║    ║ ║  ║║║  ║║║  ╠═╣  ║║║   ║║        ║    ║  ║║║  ║╣         ╠╦╝  ║ ║  ║║║  ║║║  ║╣   ╠╦╝
  ╚═╝  ╚═╝  ╩ ╩  ╩ ╩  ╩ ╩  ╝╚╝  ═╩╝        ╩═╝  ╩  ╝╚╝  ╚═╝        ╩╚═  ╚═╝  ╝╚╝  ╝╚╝  ╚═╝  ╩╚═
		  A wrapper around argp unix-style argument vector parser
  Authors:
  +  Valentino Bocchetti (matr. N86003405)
  +  Dario Morace        (matr. N86003778)
  +  Lucia Brando        (matr. N86003382)
*/

#include <argp.h>
#include <stdlib.h>

#include "command_line_runner.h"


// Argp need to find a version string to customize its content
const char *argp_program_version = "InfoPoint 1.0.0";

// Argp need to find a email address string to customize its content
const char *argp_program_bug_address = {"<" ANSI_COLOR_BRED "https://github.com/luftmensch-luftmensch/InfoPoint" ANSI_COLOR_RESET ">"};

// Argp documentation string that will be displayed in the help section.
static char info_point_doc[] = { 
  ANSI_COLOR_BMAGENTA "\tAn over engineered server for your museum" ANSI_COLOR_RESET

  "\v" ANSI_COLOR_BGREEN "AUTHORS:\n" ANSI_COLOR_RESET
  "\tWritten by Valentino Bocchetti, Dario Morace and Lucia Brando\n"
  "\vFor additional documentation please refers to " 
  "<" ANSI_COLOR_BBLUE "https://TODO.com" ANSI_COLOR_RESET ">"
};

/* The options we understand. */
static struct argp_option options[] = {
  // name, key, arg, flag, doc, group */
  /*
    This structure specifies a single option that an argp parser understands, as well as how to parse and document that option. It has the following fields: 
    + name  -> The long name for this option, corresponding to the long option ‘--name’; this field may be zero if this option only has a short name;
    + key   -> The integer key provided by the current option to the option parser.
    + arg   -> If non-zero, this is the name of an argument associated with this option, which must be provided
    + flag  -> Flags associated with this option
    + doc   -> A documentation string for this option, for printing in help messages.
    If both the name and key fields are zero, this string will be printed tabbed left
    from the normal option column, making it useful as a group header
    + group -> Group identity for this option
  */
  {"config", 'c', "FILE", 0, "Link to the config file", 0},
  {"use-default-config", 'd', 0, 0, "Use the default values embedded into the program", 0},
  { 0 }
};


/* Parse a single option */
static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  /* Get the input argument from argp_parse, which we know is a pointer to our arguments structure. */
  info_point_arguments* arguments = state->input;

  switch (key) {
    case 'c':
      arguments->config_file = arg;
      arguments->file_defined = true;
      break;
    case 'd':
      arguments->use_default_cfg = true;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }

  if(arguments->file_defined && arguments->use_default_cfg) {
    fprintf(stderr, ANSI_COLOR_RED "[%s] (%s) Cannot specify both a config file to use & use default config file!\n" ANSI_COLOR_RESET, __FILE_NAME__, __func__);
    exit(EXIT_FAILURE);
  }


  return 0;
}

static struct argp argp = {
  /* An array of argp_option structures, terminated by an entry with both NAME and KEY having a value of 0.  */
  options,

  /*  What to do with an option from this structure. */
  parse_opt,

  /*
    A string describing what other arguments are wanted by this program.
    It is only used by argp_usage to print the `Usage:' message.
    (Passing NULL as we don't need it in order to make the compiler happy)
  */
  NULL,

  /*
    Not NULL String containing extra text to be printed before and after the
    options in a long help message (separated by a vertical tab `\v' character).
  */
  info_point_doc,

  /*
    A vector of argp_children structures, terminated by a member with a 0
    argp field, pointing to child argps should be parsed with this one.
    (Passing NULL as we don't need it in order to make the compiler happy)
  */
  NULL,

  /* Filtering helper function (Passing NULL as we don't need it in order to make the compiler happy) */
  NULL,
  /*
    If non zero the string used in the argp lib are traslated using the domain
    described by the following string
    (Passing NULL as we don't need it in order to make the compiler happy)
  */
  NULL
};


/* Our argp parser. */

char* parse_command_line_arguments(int argc, char** argv){


  info_point_arguments arguments = {
    // .config_file = "undefined",
    .config_file = NULL,
    .repeat_count = 1,
    .file_defined = false
  };

  /* Parse our arguments; every option seen by parse_opt will be reflected in arguments. */
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if(arguments.file_defined == true)
    return arguments.config_file;
  return NULL;
}
