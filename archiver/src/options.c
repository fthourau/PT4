#include "../head/options.h"
#include <stdlib.h>
#include <stdbool.h>

// Default action is 'NO_ACTION', it does nothing
action_t CURRENT_ACTION = NO_ACTION;

// All flags are disabled by default
bool VERBOSE_FLAG = false;
bool ARCHIVE_NAME_FLAG = false;
bool COMPRESS_FLAG = false;
bool SPARSE_FLAG = false;
bool DIFF_FLAG = false;