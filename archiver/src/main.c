#include <stdlib.h>
#include <stdio.h>

#include "../head/archive.h"
#include "../head/extraction.h"
#include "../head/optionhandling.h"
#include "../head/options.h"
#include "../head/errors.h"
#include "../head/utilitarian.h"

int main(int argc, char** argv) {
	if(argc > 1) {
		get_options(argc, argv);

		switch(CURRENT_ACTION) {
			case CREATE:
				if(argc > 3) {
					if(is_tar_format(argv[2]))
						build_archive_from_files(argc, argv);
					else
						fprintf(stderr, "%s\n", 
								get_error_message(WRONG_ARCHIVE_FORMAT_ERR));
				}
				else if(argc == 3) {
					if(is_tar_format(argv[2]))
						fprintf(stderr, "Argument manquant: <fichier(s)>\n");
					else
						fprintf(stderr, "Un nom d'archive suffixé par '.tar' est nécessaire après les options.'\n");
				}
				else
					fprintf(stderr, "Arguments manquants: <archive> <fichier(s)>\n");
			break;
			case LIST:
				if(argv[2] != NULL)
					list_files_from_archive(argv[2]);
				else
					fprintf(stderr, "Argument manquant: <archive>\n");
			break;
			case ADD:
				if(argv[2] != NULL && argv[3] != NULL)
					add_files_to_archive(argc, argv);
				else if(argv[3] == NULL)
					fprintf(stderr, "Argument manquant: <fichier(s)>\n");
				else
					fprintf(stderr, "Argument manquant: <archive>\n");
			break;
			case UPDATE:
			break;
			case EXTRACT:
				if(argv[2] != NULL)
					extract_files_from_archive(argv[2]);
				else
					fprintf(stderr, "Argument manquant: <archive>\n");
			break;
			case DELETE:
			break;
			case HELP:
				system("cat help.man | more");
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