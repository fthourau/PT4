#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../head/options.h"
#include "../head/errors.h"
#include "../head/filehandling.h"
#include "../head/extraction.h"
#include "../head/archivehandling.h"

void diff_command(int number_of_argument, char** files) {
	FILE* archive;
	int i = first_argument_position + 1;

	if(files[first_argument_position] != NULL) {
		archive = fopen(files[first_argument_position], "r+");
	
		errno = 0;

		while(i < number_of_argument) {
			if(archive != NULL && errno == 0) {
				/*
				**	Allocation of memory blocs used for research of the file
				**	in the archive.
				**	Usage of memset() prevents the addition of old characters
				**	during new initialization process.
				*/
				char* filename = malloc(100);
				memset(filename, 0, sizeof(*filename));
				char* prefix = malloc(155);
				memset(prefix, 0, sizeof(*prefix));
				get_prefix_and_name(files[i], filename, prefix);

				int file_position = file_is_present(filename, prefix, archive);
				errno = 0;

				if(file_position != -1) {
					char* tmp_filepath = malloc(256);
					memset(tmp_filepath, 0, sizeof(*tmp_filepath));
					strcat(tmp_filepath, "/tmp/diff.");

					char* commandline = malloc(256);
					memset(commandline, 0, sizeof(*commandline));

					if(VERBOSE_FLAG)
						strcat(commandline, "diff ");
					else
						strcat(commandline, "diff -q ");

					extract_part_of_archive(file_position, archive, 
																tmp_filepath);

					strcat(commandline, "\"");
					strcat(commandline, tmp_filepath);
					strcat(commandline, "\" \"");
					strcat(commandline, files[i]);
					strcat(commandline, "\"");
					system(commandline);

					i++;

					free(tmp_filepath);
					free(commandline);
					commandline = NULL;
					tmp_filepath = NULL;
				}
				else {
					fprintf(stderr, "%s: '%s'\n", FILE_NOT_FOUND_ERR,
																	files[i]);
					i++;
					free(filename);
					free(prefix);
					filename = NULL;
					prefix = NULL;
				}

				rewind(archive);
			}
			else
				fprintf(stderr, "%s: '%s'\n", OPENING_ERR, strerror(errno));
		}
	}
}