#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

#include "../head/add.h"
#include "../head/ustarheader.h"
#include "../head/archivehandling.h"
#include "../head/options.h"
#include "../head/errors.h"
#include "../head/utilitarian.h"

bool confirmation_of_adding(char* filename);

void add_files_to_archive(int number_of_argument, char** files) {
	FILE* archive = fopen(files[first_argument_position], "r");
	errno = 0;

	if(archive != NULL && errno == 0)
		erase_ending_null_block(archive, files[first_argument_position]);
	else
		fprintf(stderr, "%s '%s' : %s\n", OPENING_ERR,
							files[first_argument_position], strerror(errno));

	int i = first_argument_position + 1;
	errno = 0;

	if(archive != NULL && errno == 0) {
		int archivesize = get_file_weight(archive);
		errno = 0;

		do {
			FILE_HEADER header;
			build_ustar_header_from_file(&header, files[i]);

			// if(file_is_present(header.name, header.prefix, archive))
				// if(!confirmation_of_adding(files[i]))
					// goto noadding;

			FILE* current_file = fopen(files[i], "r");

			if(current_file != NULL && errno == 0) {
				add_file(&header, current_file, archive);

				if(VERBOSE_FLAG)
					printf("'%s' ajouté à l'archive '%s'\n", files[i],
											files[first_argument_position]);

				fclose(current_file);
				current_file = NULL;
			}
			else
				fprintf(stderr, "%s '%s' : %s\n", OPENING_ERR, files[i],
															strerror(errno));
// noadding:
			i++;
		} while(i < number_of_argument);

		// Write the null-block only if the archive has changed
		if(archivesize <= get_file_weight(archive))
			write_null_block(archive);

		fclose(archive);
		archive = NULL;
	}
	else
		fprintf(stderr, "%s '%s' : %s\n", OPENING_ERR, files[i],
														strerror(errno));
}

void add_file(FILE_HEADER* header, FILE* file, FILE* archive) {
	size_t filesize = oct2dec(header->size);
	char* buffer = malloc(filesize);
	memset(buffer, 0, filesize);

	unsigned int space_needed = calculate_number_of_block(filesize);
	space_needed *= BLOCK_SIZE;

	fread(buffer, filesize, 1, file);
	write_header_to_archive(header, archive);
	fwrite(buffer, filesize, 1, archive);

	complete_current_block(filesize, space_needed, archive);

	free(buffer);
	buffer = NULL;
}

bool confirmation_of_adding(char* filename) {
	char answer[1];
	printf("Le fichier '%s' est déjà archivé, l'ajouter quand même ? (Y/N)",
																	filename);
	scanf("%c", answer);

	return ( ( answer[0] == 'y' || 
			   answer[0] == 'Y' ||
			   answer[0] == 'o' ||
			   answer[0] == 'O') ? true : false );
}