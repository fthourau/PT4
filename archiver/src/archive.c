#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <fcntl.h>

#include "../head/options.h"
#include "../head/archive.h"
#include "../head/errors.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

void get_file_info_verbose(FILE_HEADER header) {
	printf( (header.typeflag[0] == '5') ? "d" : "-");
	// Get rights of file
    printf("%s", get_rights(header.mode[4]));
    printf("%s", get_rights(header.mode[5]));
    printf("%s", get_rights(header.mode[6]));
    printf(" %s %s ", header.uname, header.gname);
    printf_weight(oct2dec(header.size));
    printf_date(oct2dec(header.mtime));
    printf("\t%s\n", header.name);
    // touch -d -> edit mtime
	// touch -d "`date -d @1360884899 '+%Y-%m-%d %H:%M:%S'`" <filename>
}

// This function calculates the number of 512 bytes block according to the
// filesize
unsigned int calculate_number_of_block(size_t filesize) {
	unsigned int nbr_of_block = filesize / BLOCK_SIZE;

	if((filesize % BLOCK_SIZE) > 0)
		nbr_of_block++;

	return nbr_of_block;
}

// Research if a file named "prefix/filename" is present inside the archive
// If it's present, return the position of the cursor just before the header
// otherwise returns -1
int file_is_present(char* filename, char* prefix, FILE* archive) {
	bool end_of_archive = false;
	FILE_HEADER header;
	size_t filesize;
	unsigned int cursor_pos = -1;
	unsigned int cursor_offset, nbr_of_block;

	do {
		build_ustar_header_from_archive(&header, archive);

		if(header.name != NULL && (int)header.name[0] > 32) {
			if(header.name == filename && header.prefix == prefix) {
				cursor_pos = ftell(archive) - HEADER_S;
				end_of_archive = true;
			}
			else {
				filesize = oct2dec(header.size);
				nbr_of_block = calculate_number_of_block(filesize);
				cursor_offset = (BLOCK_SIZE *  nbr_of_block);
				fseek(archive, cursor_offset, SEEK_CUR);
			}
		}
		else
			end_of_archive = true;
	} while(!end_of_archive);

	rewind(archive);

	return cursor_pos;
}

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

void list_files_from_archive(char* archive_path) {
	errno = 0;
	FILE* archive = fopen(archive_path, "r");

	if(archive != NULL && errno == 0) {
		if(VERBOSE_FLAG)
			printf("Listage du contenu de '%s':\n", archive_path);

		FILE_HEADER header;
		unsigned int cursor_offset, nbr_of_block;
		bool end_of_archive = false;

		build_ustar_header_from_archive(&header, archive);

		do {
			if(header.name != NULL && (int)header.name[0] > 32) {
				int filesize = oct2dec(header.size);

				if(VERBOSE_FLAG)
					get_file_info_verbose(header);
				else
					printf("%s%s\n", header.prefix, header.name);

				// Figuring out number of file content's block for the offset
				nbr_of_block = calculate_number_of_block(filesize);

				cursor_offset = (BLOCK_SIZE * nbr_of_block);

				// Applying offset to the file from the current cursor position
				fseek(archive, cursor_offset, SEEK_CUR);

				// Then, get the next header
				build_ustar_header_from_archive(&header, archive);
			}
			else
				end_of_archive = true;
		} while(!end_of_archive);
	}
	else {
		fprintf(stderr, "%s '%s': %s\n", INVALID_FILE_ERR, archive_path,
															strerror(errno));
	}
}