#include <stdlib.h>
#include <string.h>

#include "../head/add.h"
#include "../head/create.h"
#include "../head/delete.h"
#include "../head/diff.h"
#include "../head/errors.h"
#include "../head/extract.h"
#include "../head/filehandling.h"
#include "../head/list.h"
#include "../head/optionhandling.h"
#include "../head/options.h"
#include "../head/test.h"
#include "../head/update.h"
#include "../head/utilitarian.h"

static bool MARKED_FOR_DELETION = false;

void uncompress_and_change_path(char** files);
void delete_temporary_file(char* file);

int main(int argc, char** argv) {
	if(strcmp(argv[1], "test") == 0)
		test();

	if(argc > 1) {
		get_options(argc, argv);

		//  If the archive is compressed we have to uncompress it before any
		//  action
		if( argv[first_argument_position] != NULL &&
			is_gzip_format(argv[first_argument_position]) ) {
			uncompress_and_change_path(argv);
			MARKED_FOR_DELETION = true;
		}

		switch(CURRENT_ACTION) {
			case CREATE:
				if(argc > 3)
					create_archive_from_files(argc, argv);
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
					add_files_to_archive(argc, argv);
				else if(argc == 3)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case UPDATE:
				if(argc > 3)
					update_files_from_archive(argc, argv);
				else if(argc == 3)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case EXTRACT:
				if(argv[first_argument_position] != NULL)
					extract_files_from_archive(argv[first_argument_position]);
				else
					fprintf(stderr, "%s\n", ARCHIVE_ARG_MISSING_ERR);
			break;
			case DELETE:
				if(argc > 3)
					delete_files_from_archive(argc, argv);
				else if(argc == 3)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case DIFF:
				if(argc > 3)
					diff_command(argc, argv);
				else if(argc == 3)
					fprintf(stderr, "%s\n", FILE_ARG_MISSING_ERR);
				else
					fprintf(stderr, "%s\n", ALL_ARG_MISSING_ERR);
			break;
			case HELP:
				system("cat help.man | more");
			break;
			case NO_ACTION:
				fprintf(stderr, "%s\n", NO_ACTION_ERR);
			break;
		}

		// If the archive is compressed, we have to delete the simple tar
		if(COMPRESS_FLAG) {
			// If the archive was compressed before any action, we have to
			// compress it again
			if(MARKED_FOR_DELETION)
				compress_with_gzip(argv[first_argument_position]);
			
			delete_temporary_file(argv[first_argument_position]);
		}
	}
	else
		fprintf(stderr, "%s\n", NO_ARGUMENT_ERR);

	return EXIT_SUCCESS;
}

void uncompress_and_change_path(char** files) {
	int len = strlen(files[first_argument_position]);

	decompress_with_gzip(files[first_argument_position]);

	// Removing of the .gz suffix. Uncompress archive has the same name
	files[first_argument_position][len - 3] = '\0';
	files[first_argument_position][len - 2] = '\0';
	files[first_argument_position][len - 1] = '\0';
}

void delete_temporary_file(char* file) {
	char buffer[260] = { "rm -rf " };
	strcat(buffer, file);
	system(buffer);
}