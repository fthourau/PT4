#include "../head/options.h"
#include <stdlib.h>
#include <stdbool.h>

bool VERBOSE_FLAG = false;

void activate_verbose() {
	VERBOSE_FLAG = true;
}

void display_help() {
	system("cat help.man | more");
}