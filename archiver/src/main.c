#include <stdlib.h>
#include <stdio.h>

#include "../head/archive.h"
#include "../head/delete.h"
#include "../head/list.h"
#include "../head/extraction.h"
#include "../head/diff.h"
#include "../head/optionhandling.h"
#include "../head/options.h"
#include "../head/errors.h"
#include "../head/utilitarian.h"

int main(int argc, char** argv) {
	if(argc > 1) {
		get_options(argc, argv);

		switch(CURRENT_ACTION) {
			case CREATE:
				if(argc > 3)
					build_or_add_archive_from_files(argc, argv);
				else if(argc == 3)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case LIST:
				if(argv[first_argument_position] != NULL)
					list_files_from_archive(argv[first_argument_position]);
				else
					fprintf(stderr, "%s\n", ARCHIVE_ARG_MISSING_ERR);
			break;
			case ADD:
				if(argc > 3)
					build_or_add_archive_from_files(argc, argv);
				else if(argc == 3)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case UPDATE:
			break;
			case EXTRACT:
				if(argv[first_argument_position] != NULL)
					extract_files_from_archive(argv[first_argument_position]);
				else
					fprintf(stderr, "%s\n", ARCHIVE_ARG_MISSING_ERR);
			break;
			case DELETE:
			if(argv[2] != NULL)
				delete_files_from_archive(argc, argv);
			break;
			case DIFF:
				if(argv[2] != NULL)
					diff_command(argc, argv);
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