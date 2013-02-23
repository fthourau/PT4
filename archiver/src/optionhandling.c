#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../head/options.h"

const int NB_OPTIONS = 9; //constante qui défini le nombre d'option

void get_options(int argc, char **argv) {
	int c; //variable du switch (elle contient les caractères d'options)

	while (1) {
		static struct option long_options[] =
		{
			{"add",     no_argument, 0, 'a'},
			{"append",  no_argument, 0, 'b'},
			{"help",  no_argument, 0, 'h'},
			{"verbose",  no_argument, 0, 'v'},
			{"delete",  required_argument, 0, 'd'},
			{"create",  required_argument, 0, 'c'},
			{"file",    required_argument, 0, 'f'},
			{"extract", required_argument, 0, 'x'},
			{"list", required_argument, 0, 'l'},

			{0, 0, 0, 0}
		};
		/* getopt_long stock l'index de l'option ici */
		int option_index = 0;
		
		c = getopt_long(argc, argv, "abvhc:d:f:x:l:", long_options, 
															&option_index);

		/* Detecte la fin des options */
		if(c == -1)
			break;

		switch(c) {
			case 0:
				if(long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
			break;
			case 'a':
				CURRENT_ACTION = ADD;
			break;
			case 'v':
				VERBOSE_FLAG = true;
			break;
			case 'b':
				puts("option -b\n");
			break;
			case 'c':
				CURRENT_ACTION = CREATE;
			break;
			case 'x' :
				CURRENT_ACTION = EXTRACT;
			break;
			case 'l':
				CURRENT_ACTION = LIST;
			break;
			case 'd':
				printf("option -d with value `%s'\n", optarg);
			break;

			case 'f':
				printf("option -f with value `%s'\n", optarg);
			break;

			case 'h':
				CURRENT_ACTION = HELP;
			break;
			case '?':
				//message d'erreur
			break;
			default:
				abort();
		}
	}
}
