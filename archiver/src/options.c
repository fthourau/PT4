#include "../head/options.h"

// Default action is 'NO_ACTION', it does nothing
action_t CURRENT_ACTION = NO_ACTION;

int first_argument_position = 2;

int option_checking = 0;

// All flags are disabled by default
bool VERBOSE_FLAG = false;
bool MAKE_ARCHIVE_FLAG = false;
bool COMPRESS_FLAG = false;
bool SPARSE_FLAG = false;

int SPARSE_ACCURACY = 20;