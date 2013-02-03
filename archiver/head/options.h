#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <stdbool.h>

// Options' flags
extern bool VERBOSE_FLAG;

// Options' flags' modifiers
void activate_verbose();

// This command is used in order to display help on terminal
void display_help();

#endif