#include <stdio.h>
#include <stdlib.h>
#include "../head/optget.h"

static int verbose_flag;

int main (int argc, char **argv){

	optget(argc,argv);

	return 0;
}