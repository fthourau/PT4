#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../head/options.h"
#include "../head/errors.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

static unsigned int BLOCK_SIZE = 512;

void recover_filestats(FILE_HEADER* header);
void extraction(int read_size, int write_size,	FILE* archive, FILE* file);

void extract_files_from_archive(char* archive_path) {
	errno = 0;
	FILE* archive = fopen(archive_path, "r");

	if(archive != NULL && errno == 0) {
		FILE_HEADER header;
		unsigned int nbr_of_block;
		bool end_of_archive = false;

		if(VERBOSE_FLAG)
			printf("Extraction en cours ...\n");

		build_ustar_header_from_archive(&header, archive);

		do {
			if(header.name != NULL && (int)header.name[0] > 32) {
				errno = 0;
				
				// Get size and create output file
				size_t filesize = oct2dec(header.size);
				FILE* output_file = fopen(header.name, "w+");

				if(output_file != NULL && errno == 0) {
					nbr_of_block = filesize / BLOCK_SIZE;

					if((filesize % BLOCK_SIZE) > 0)
						nbr_of_block++;

					// Get the content from the archive
					extraction((BLOCK_SIZE * nbr_of_block), filesize,
														archive, output_file);

					if(VERBOSE_FLAG)
						printf("Extrait: %s\n", header.name);

					fclose(output_file);
					output_file = NULL;
					recover_filestats(&header);
					build_ustar_header_from_archive(&header, archive);
				}
				else
					fprintf(stderr, "Extraction impossible sur '%s': %s\n", 
												header.name, strerror(errno));
			}
			else
				end_of_archive = true;
		} while(!end_of_archive);

		fclose(archive);
		archive = NULL;
	}
	else
		fprintf(stderr, "Fichier invalide '%s': %s\n", archive_path,
															strerror(errno));
}

void extract_part_of_archive(int from, FILE* archive, char* path) {
	FILE_HEADER header;
	FILE* file;
	unsigned long long int filesize;
	
	fseek(archive, from, SEEK_SET);
	errno = 0;

	build_ustar_header_from_archive(&header, archive);
	filesize = oct2dec(header.size);

	if(path[0] <= 32)
		strcat(path, header.prefix);
	
	strcat(path, header.name);

	file = fopen(path, "w");

	if(file != NULL && errno == 0) {
		extraction(filesize, filesize, archive, file);
		fclose(file);
	}
	else
		fprintf(stderr, "%s: '%s'\n", TMP_FILE_OPENING_ERR, strerror(errno));
}

void recover_filestats(FILE_HEADER* header) {
	// Recover the modification time
	struct utimbuf times;
	times.actime = time(NULL);
	times.modtime = oct2dec(header->mtime);
	utime(header->name, &times);

	// Recover UID and GID on file
	chown(header->name, oct2dec(header->uid), oct2dec(header->gid));

	// Recover UNIX rights on file
	mode_t permissions = oct2dec(header->mode);
	chmod(header->name, permissions);
}

void extraction(int read_size, int write_size, FILE* archive, FILE* file) {
	if(write_size > read_size)
		fprintf(stderr, "%s\n", OVERRIDE_LIMIT_ERR);
	else {
		char* buffer = malloc(read_size);
		fread(buffer, read_size, 1, archive);
		fwrite(buffer, write_size, 1, file);
		free(buffer);
		buffer = NULL;
	}
}