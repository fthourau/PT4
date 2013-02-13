#include "../head/options.h"
#include <stdlib.h>
#include <stdbool.h>

bool VERBOSE_FLAG = false;

void display_help() {
	system("cat help.man | more");
}