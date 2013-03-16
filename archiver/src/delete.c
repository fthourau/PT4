#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../head/delete.h"
#include "../head/ustarheader.h"
#include "../head/filehandling.h"
#include "../head/archivehandling.h"
#include "../head/options.h"
#include "../head/errors.h"
#include "../head/utilitarian.h"

void rename_temporary_archive(char* archive_name);

void delete_files_from_archive(int number_of_argument, char** files) {
	int i = first_argument_position + 1;

	if(VERBOSE_FLAG)
		printf("Suppression de fichier(s) à l'archive '%s' en cours...\n", 
											files[first_argument_position]);

	do {
		FILE* archive = fopen(files[first_argument_position], "r+");
		errno = 0;

		if(archive != NULL && errno == 0) {
			char* filename = malloc(NAME_S);
			memset(filename, 0, NAME_S);
			char* prefix = malloc(PREFIX_S);
			memset(prefix, 0, PREFIX_S);
			get_prefix_and_name(files[i], filename, prefix);

			int file_position = file_is_present(filename, prefix, archive);

			if(file_position != -1) {
				delete_file(file_position, archive, 
											files[first_argument_position]);

				fclose(archive);
				archive = NULL;

				if(VERBOSE_FLAG)
					printf("'%s' supprimé de l'archive.\n", files[i]);
			}
			else
				fprintf(stderr, "%s: %s\n", FILE_NOT_FOUND_ERR, files[i]);

			free(filename);
			free(prefix);
			filename = NULL;
			prefix = NULL;

			i++;
		}
		else
			fprintf(stderr, "%s '%s': %s\n", INVALID_FILE_ERR,
							files[first_argument_position], strerror(errno));

		if(archive != NULL) {
			fclose(archive);
			archive = NULL;
		}
	} while(i < number_of_argument);
}

void delete_file(int file_position, FILE* archive, char* archive_name) {
	FILE_HEADER header;
	FILE* new_archive = fopen("archive.tmp", "w");
	size_t archive_size = get_file_weight(archive);
	char* buffer = malloc(archive_size);
	memset(buffer, 0, archive_size);

	if(file_position != 0) {
		fread(buffer, file_position, 1, archive);
		fwrite(buffer, file_position, 1, new_archive);
	}
	
	build_ustar_header_from_archive(&header, archive);

	size_t filesize = oct2dec(header.size);
	int number_of_block = calculate_number_of_block(filesize);
	int size_skipped = BLOCK_SIZE * number_of_block;

	fseek(archive, size_skipped, SEEK_CUR);
	memset(buffer, 0, sizeof(*buffer));

	int remaining_size = archive_size - ftell(archive);

	fread(buffer, remaining_size, 1, archive);
	fwrite(buffer, remaining_size, 1, new_archive);

	free(buffer);
	buffer = NULL;

	fclose(new_archive);
	fclose(archive);
	new_archive = NULL;
	archive = NULL;

	rename_temporary_archive(archive_name);

	archive = fopen(archive_name, "r+");
}

void rename_temporary_archive(char* archive_name) {
	char* rename_command = malloc(130);
	memset(rename_command, 0, 130);
	strcat(rename_command, "mv archive.tmp ");
	strcat(rename_command, archive_name);
	
	system(rename_command);

	free(rename_command);
	rename_command = NULL;
}