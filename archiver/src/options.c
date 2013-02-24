#include "../head/options.h"

#include <stdlib.h>

// Default action is 'NO_ACTION', it does nothing
action_t CURRENT_ACTION = NO_ACTION;

// All flags are disabled by default
bool VERBOSE_FLAG = false;
bool MAKE_ARCHIVE_FLAG = false;
bool COMPRESS_FLAG = false;
bool SPARSE_FLAG = false;
bool DIFF_FLAG = false;