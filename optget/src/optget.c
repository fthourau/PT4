#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "../head/util.h"
#include "../head/archive.h"
#include "../head/options.h"

const int NB_OPTIONS = 8; //constante qui défini le nombre d'option

void optget(int argc, char **argv){
	int c; //variable du switch (elle contient les caractères d'option)s
	int i; // variable d'une boucle dans le switch
	FILE* archive = NULL;
	while (1)
	{
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
		
		c = getopt_long (argc, argv, "abvhc:d:f:x:l:",
		long_options, &option_index);

		/* Detect la fin des options */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
			break;

			case 'a':
				puts ("option -a\n");
			break;

			case 'v':
				VERBOSE_FLAG = true;
			break;

			case 'b':
				puts ("option -b\n");
			break;

			case 'c':
				printf ("option -c with value `%s'\n", optarg);
			break;
			case 'x' :
				archive = fopen(argv[2], "r");
				if(archive != NULL) {
					// extract_files_from_archive(archive);
					extract_files_from_archive(archive);
					fclose(archive);
				}
			break;
			case 'l':
				archive = fopen(argv[2], "r");
				if(archive != NULL) {
					// extract_files_from_archive(archive);
					list_files_from_archive(archive);
					fclose(archive);
				}
			break;
			case 'd':
				printf ("option -d with value `%s'\n", optarg);
			break;

			case 'f':
				printf ("option -f with value `%s'\n", optarg);
			break;

			case 'h':
				for(i = 0 ; i < NB_OPTIONS ; i++){
				printf("L'option : --%s ou -%c  %s \n",long_options[i].name,long_options[i].val,argument(long_options[i].has_arg));	
				}
			break;

			case '?':
				//message d'erreur
			break;

			default:
				abort();
		}
	}
	

	if (optind < argc)
	{
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		printf ("n'est pas une option\n");
		
	}

	exit (0);
}

