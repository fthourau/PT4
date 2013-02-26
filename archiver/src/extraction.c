#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../head/options.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

static unsigned int BLOCK_SIZE = 512;

void recover_filestats(FILE_HEADER* header);

void extract_files_from_archive(char* archive_path) {
	errno = 0;
	FILE* archive = fopen(archive_path, "r");

	if(archive != NULL && errno == 0) {
		FILE_HEADER header;
		unsigned int cursor_pos, nbr_of_block;
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
					cursor_pos = 0;
					nbr_of_block = filesize / BLOCK_SIZE;

					if((filesize % BLOCK_SIZE) > 0)
						nbr_of_block++;

					// Get the content from the archive
					while(cursor_pos < (BLOCK_SIZE * nbr_of_block)) {
						if(cursor_pos >= filesize)
							fgetc(archive);
						else
							fputc(fgetc(archive), output_file);
						
						cursor_pos++;
					}

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