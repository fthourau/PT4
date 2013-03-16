#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>

#include "../head/add.h"
#include "../head/archivehandling.h"
#include "../head/delete.h"
#include "../head/errors.h"
#include "../head/filehandling.h"
#include "../head/options.h"
#include "../head/ustarheader.h"

void update_files_from_archive(int number_of_argument, char** files) {
	int i = first_argument_position;
	FILE* archive = fopen(files[i], "r+");
	errno = 0;

	if(archive != NULL && errno == 0) {
		erase_ending_null_block(archive, files[i]);
		fclose(archive);
		archive = NULL;
		errno = 0;
		i++;
	}
	else
		goto error;

	if(VERBOSE_FLAG)
		printf("Mise à jour de fichier(s) de l'archive '%s' en cours...\n", 
											files[first_argument_position]);

	do {
		archive = fopen(files[first_argument_position], "r+");

		if(archive != NULL && errno == 0) {
			errno = 0;
			FILE_HEADER new_file_header;
			build_ustar_header_from_file(&new_file_header, files[i]);

			int file_position = file_is_present(new_file_header.name, 
												new_file_header.prefix,
												archive);

			if(file_position != -1) {
				fseek(archive, file_position, SEEK_SET);

				FILE_HEADER current_file_header;
				build_ustar_header_from_archive(&current_file_header,
												archive);

				if( atoi(current_file_header.mtime) <
					atoi(new_file_header.mtime) ) {
					FILE* new_file = fopen(files[i], "r");

					if(new_file != NULL && errno == 0) {
						delete_file(file_position, archive, 
											files[first_argument_position]);

						if(archive != NULL) {
							fseek(archive, 0, SEEK_END);
							add_file(&new_file_header, new_file, archive);
						}
						else
							goto error;

						fclose(new_file);
						new_file = NULL;

						if(VERBOSE_FLAG)
							printf("'%s' a été mis à jour.\n", files[i]);
					}
					else {
						fprintf(stderr, "%s '%s' : %s\n", OPENING_ERR, 
												files[i], strerror(errno));
						fprintf(stderr, "%s '%s'\n", UPDATE_ERR, files[i]);
					}
				}
				else
					if(VERBOSE_FLAG)
						printf("'%s' est déjà à jour.\n", files[i]);
			}
			else
				fprintf(stderr, "%s: %s\n", FILE_NOT_FOUND_ERR, files[i]);
		}
		else
			goto error;

		i++;

		if(i == number_of_argument)
			write_null_block(archive);

		fclose(archive);
		archive = NULL;
	} while(i < number_of_argument);

// Here is a jump in case of an error during opening the archive
error:
	// Avoid a wrong error display at the end of the function
	if(i != number_of_argument)
		fprintf(stderr, "%s '%s' : %s\n", OPENING_ERR, files[i],
															strerror(errno));
}