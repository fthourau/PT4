#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../head/archive.h"
#include "../head/optionhandling.h"
#include "../head/options.h"

int main(int argc, char** argv) {
	// Getting the options only if specified
	if(argv[1] != NULL) {
		get_options(argc, argv);
		
		errno = 0;

		switch(CURRENT_ACTION) {
			case CREATE:
				build_archive_from_files(argc, argv);
			break;
			case LIST:
				if(argv[2] != NULL)
					list_files_from_archive(argv[2]);
				else
					fprintf(stderr, "Argument manquant: %s\n", strerror(errno));
			break;
			case ADD:
			break;
			case UPDATE:
			break;
			case EXTRACT:
				if(argv[2] != NULL)
					extract_files_from_archive(argv[2]);
				else
					fprintf(stderr, "Argument manquant: %s\n", strerror(errno));
			break;
			case DELETE:
			break;
			case HELP:
				printf("HELP ...\n");
				system("cat help.man");
			break;
			case NO_ACTION:
				fprintf(stderr, "Aucune action à effectuer ...\n");
			break;
		}
	}
	else
		fprintf(stderr, "Aucun argument: 'tar -h' pour voir le manuel ...\n");

	return EXIT_SUCCESS;
}