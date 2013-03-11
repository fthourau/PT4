#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <fcntl.h>

#include "../head/options.h"
#include "../head/archive.h"
#include "../head/errors.h"
#include "../head/ustarheader.h"
#include "../head/archivehandling.h"
#include "../head/utilitarian.h"

// This function is made for building an archive (or adding to an existing one
// ) from a list of files
void build_or_add_archive_from_files(int number_of_arguments, char** files) {
	FILE_HEADER header;
	FILE* archive = NULL;
	FILE* current_file = NULL;
	int i = first_argument_position + 1;
	unsigned int cursor_pos, nbr_of_block;
	size_t filesize;

	errno = 0;

	if(files[first_argument_position] != NULL) {
		if(CURRENT_ACTION == CREATE)
			archive = fopen(files[first_argument_position], "w");
		else
			archive = fopen(files[first_argument_position], "r+");
	}

	if(archive != NULL && errno == 0) {
		errno = 0;

		// In order to delete ending block of null-terminated
		if(CURRENT_ACTION == ADD)
			fseek(archive, -BLOCK_SIZE, SEEK_END);	

		if(VERBOSE_FLAG && MAKE_ARCHIVE_FLAG) {
			if(CURRENT_ACTION == CREATE)
				printf("Création de l'archive '%s' en cours ...\n",
											files[first_argument_position]);
			else if(CURRENT_ACTION == ADD)
				printf("Ajout à '%s' en cours ...\n",
											files[first_argument_position]);
		}

		do {
			current_file = fopen(files[i], "r");
			
			if(current_file != NULL && errno == 0) {
				build_ustar_header_from_file(&header, files[i]);

				if(MAKE_ARCHIVE_FLAG) {
					write_header_to_archive(&header, archive);

					if(VERBOSE_FLAG)
						printf("===> %s ajouté à l'archive.\n", header.name);
				}
				else
					printf_header(&header);
				
				// Only if it's a regular file
				if(header.typeflag[0] == '0') {
					filesize = oct2dec(header.size);

					cursor_pos = 0;
					nbr_of_block = calculate_number_of_block(filesize);

					while(cursor_pos < (BLOCK_SIZE * nbr_of_block)) {
						if(MAKE_ARCHIVE_FLAG) {
							if(cursor_pos >= filesize)
								fputc('\0', archive);
							else
								fputc(fgetc(current_file), archive);
						}
						else {
							if(cursor_pos < filesize)
								printf("%c", fgetc(current_file));
						}
						
						cursor_pos++;
					}

					fclose(current_file);
					current_file = NULL;
				}
			}
			else
				fprintf(stderr, "%s '%s': %s\n", OPENING_ERR, header.name,
															strerror(errno));

			i++;
		} while(i < number_of_arguments);

		for(i = 0; i < BLOCK_SIZE; i++)
			fputc('\0', archive);

		fclose(archive);
		archive = NULL;

		if(COMPRESS_FLAG)
			compress_with_gzip(files[first_argument_position]);
	}
	else
		fprintf(stderr, "%s '%s': %s\n", INVALID_FILE_ERR, files[2], 
															strerror(errno));
}