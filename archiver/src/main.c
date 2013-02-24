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
						build_or_add_archive_from_files(argc, argv, 0);
					else
						fprintf(stderr, "%s\n", WRONG_ARCHIVE_FORMAT_ERR);
				}
				else if(argc == 3) {
					if(is_tar_format(argv[2]))
						fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
					else
						fprintf(stderr, "%s\n", WRONG_ARCHIVE_FORMAT_ERR);
				}
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case LIST:
				if(argv[2] != NULL)
					list_files_from_archive(argv[2]);
				else
					fprintf(stderr, "%s\n", ARCHIVE_ARG_MISSING_ERR);
			break;
			case ADD:
				if(argv[2] != NULL && argv[3] != NULL)
					build_or_add_archive_from_files(argc, argv,1);
				else if(argv[3] == NULL)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ARCHIVE_ARG_MISSING_ERR);
			break;
			case UPDATE:
			break;
			case EXTRACT:
				if(argv[2] != NULL)
					extract_files_from_archive(argv[2]);
				else
					fprintf(stderr, "%s\n", ARCHIVE_ARG_MISSING_ERR);
			break;
			case DELETE:
			break;
			case HELP:
				system("cat help.man | more");
			break;
			case NO_ACTION:
				fprintf(stderr, "%s\n", NO_ACTION_ERR);
			break;
		}
	}
	else
		fprintf(stderr, "%s\n", NO_ARGUMENT_ERR);

	return EXIT_SUCCESS;
}