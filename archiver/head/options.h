#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

// Enumeration of main possible actions
typedef enum ACTION_T {
	CREATE,
	LIST,
	ADD,
	UPDATE,
	EXTRACT,
	DELETE,
	DIFF,
	HELP,
	NO_ACTION
} action_t;

// Action that will be choose by the user
extern action_t CURRENT_ACTION;

// Position of the first argument
extern int first_argument_position;

// Check if it's a right combination of options
extern int option_checking;

// Options' flags
extern bool VERBOSE_FLAG;
extern bool MAKE_ARCHIVE_FLAG;
extern bool COMPRESS_FLAG;
extern bool SPARSE_FLAG;

#endif