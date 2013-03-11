#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../head/options.h"
#include "../head/errors.h"

const int NB_OPTIONS = 12; //constante qui défini le nombre d'option

void get_options(int argc, char **argv) {
	int c, i; //variable du switch (elle contient les caractères d'options)

	for(i = 2; i < argc; ++i)
		if(argv[i][0] == '-')
			first_argument_position++;

	while (1) {
		static struct option long_options[] =
		{
			{"create",  no_argument, 0, 'c'},
			{"list", no_argument, 0, 't'},
			{"add",     no_argument, 0, 'r'},
			{"update",  no_argument, 0, 'u'},
			{"extract", no_argument, 0, 'x'},
			{"delete",  no_argument, 0, 'd'},
			{"help",  no_argument, 0, 'h'},
			{"verbose",  no_argument, 0, 'v'},
			{"file",    no_argument, 0, 'f'},
			{"compress",    no_argument, 0, 'z'},
			{"sparse", no_argument, 0, 's'},
			{"diff", no_argument, 0, 'm'},

			{0, 0, 0, 0}
		};
		/* getopt_long stock l'index de l'option ici */
		int option_index = 0;
		
		c = getopt_long(argc, argv, "hvfzsmctruxd", long_options, 
															&option_index);

		/* Detecte la fin des options */
		if(c == -1)
			break;

		switch(c) {
			case 'c':
				CURRENT_ACTION = CREATE;
				option_checking++;
			break;
			case 't':
				CURRENT_ACTION = LIST;
				option_checking++;
			break;
			case 'r':
				CURRENT_ACTION = ADD;
				option_checking++;
			break;
			case 'u':
				CURRENT_ACTION = UPDATE;
				option_checking++;
			break;
			case 'x' :
				CURRENT_ACTION = EXTRACT;
				option_checking++;
			break;
			case 'd':
				CURRENT_ACTION = DELETE;
				option_checking++;
			break;
			case 'm':
				CURRENT_ACTION = DIFF;
				option_checking++;
			break;
			case 'h':
				CURRENT_ACTION = HELP;
				option_checking++;
			break;
			case 'v':
				VERBOSE_FLAG = true;
			break;
			case 'f':
				MAKE_ARCHIVE_FLAG = true;
			break;
			case 'z':
				COMPRESS_FLAG = true;
			break;
			case 's':
				SPARSE_FLAG = true;
			break;
			default:
				fprintf(stderr, "%s\n", UNKNOWN_OPTION_ERR);
				exit(EXIT_FAILURE);
			break;
		}

		if(option_checking > 1) {
			fprintf(stderr, "%s\n", INVALID_OPTION_COMBINATION_ERR);
			exit(EXIT_FAILURE);
		}
	}
}
