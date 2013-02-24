#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../head/options.h"
#include "../head/errors.h"

const int NB_OPTIONS = 12; //constante qui défini le nombre d'option

void get_options(int argc, char **argv) {
	int c; //variable du switch (elle contient les caractères d'options)

	while (1) {
		static struct option long_options[] =
		{
			{"create",  required_argument, 0, 'c'},
			{"list", required_argument, 0, 't'},
			{"add",     no_argument, 0, 'r'},
			{"update",  no_argument, 0, 'u'},
			{"extract", required_argument, 0, 'x'},
			{"delete",  required_argument, 0, 'd'},
			{"help",  no_argument, 0, 'h'},
			{"verbose",  no_argument, 0, 'v'},
			{"file",    required_argument, 0, 'f'},
			{"compress",    required_argument, 0, 'z'},
			{"sparse", required_argument, 0, 's'},
			{"diff", required_argument, 0, 'm'},

			{0, 0, 0, 0}
		};
		/* getopt_long stock l'index de l'option ici */
		int option_index = 0;
		
		c = getopt_long(argc, argv, "hvfzsmc:t:r:u:x:d:", long_options, 
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
			case 'c':
				CURRENT_ACTION = CREATE;
			break;
			case 't':
				CURRENT_ACTION = LIST;
			break;
			case 'r':
				CURRENT_ACTION = ADD;
			break;
			case 'u':
				CURRENT_ACTION = UPDATE;
			break;
			case 'x' :
				CURRENT_ACTION = EXTRACT;
			break;
			case 'd':
				CURRENT_ACTION = DELETE;
			break;
			case 'h':
				CURRENT_ACTION = HELP;
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
			case 'm':
				DIFF_FLAG = true;
			break;
			default:
				fprintf(stderr, "%s\n", UNKNOWN_OPTION_ERR);
				exit(EXIT_FAILURE);
		}
	}

//================>	A supprimer ?
	/*if(optind < argc) {
		while(optind < argc)
			printf ("%s ", argv[optind++]);
		
		printf ("n'est pas une option\n");	
	}*/
//<================
}
