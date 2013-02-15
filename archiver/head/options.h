#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <stdbool.h>

// Enumeration of main possible actions
typedef enum ACTION_T {
	CREATE,
	LIST,
	ADD,
	UPDATE,
	EXTRACT,
	DELETE,
	HELP,
	NO_ACTION
} action_t;

// Action that will be choose by the user
extern action_t CURRENT_ACTION;

// Options' flags
extern bool VERBOSE_FLAG;
extern bool ARCHIVE_NAME_FLAG;
extern bool COMPRESS_FLAG;
extern bool SPARSE_FLAG;
extern bool DIFF_FLAG;

#endif