#include <string.h>
#include <malloc.h>
#include <errno.h>

#include "../head/options.h"
#include "../head/errors.h"
#include "../head/ustarheader.h"
#include "../head/archivehandling.h"
#include "../head/utilitarian.h"

void create_archive_from_files(int number_of_arguments, char** files) {
	FILE* archive = NULL;
	int i = first_argument_position;
	errno = 0;

	// If the user wants to create the archive file so the first argument is
	// the name of the archive.
	if(MAKE_ARCHIVE_FLAG) {
		archive = fopen(files[first_argument_position], "w");
		
		if(archive == NULL && errno != 0)
			goto error;

		i++;
	}

	do {
		errno = 0;
		FILE* current_file = fopen(files[i], "r");

		if(current_file == NULL && errno != 0)
			goto error;
		
		FILE_HEADER header;
		build_ustar_header_from_file(&header, files[i]);
		size_t filesize = oct2dec(header.size);
		char* buffer = malloc(filesize);
		memset(buffer, 0, filesize);

		fread(buffer, filesize, 1, current_file);

		if(MAKE_ARCHIVE_FLAG) {
			write_header_to_archive(&header, archive);
			fwrite(buffer, filesize, 1, archive);

			unsigned int space_needed = calculate_number_of_block(filesize);
			space_needed *= BLOCK_SIZE;
			
			complete_current_block(filesize, space_needed, archive);

			if(VERBOSE_FLAG)
				printf("'%s' a été archivé.\n", files[i]);
		}
		else {
			printf_header(&header);
			printf("%.*s\n", filesize, buffer);
		}

		free(buffer);
		buffer = NULL;

		fclose(current_file);
		current_file = NULL;

		i++;
	} while(i < number_of_arguments);

	// Write an ending null block at the end of the archive
	if(MAKE_ARCHIVE_FLAG) {
		write_null_block(archive);
		fclose(archive);
		archive = NULL;
	}

// Here is a jump in case of an error during opening the archive
error:
	// Avoid a wrong error display at the end of the function
	if(i != number_of_arguments)
		fprintf(stderr, "%s '%s' : %s\n", OPENING_ERR, files[i],
															strerror(errno));
}
