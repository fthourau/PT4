#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <fcntl.h>

#include "../head/archive.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

#define BLOC_SIZE 512

int get_file_weight(FILE* file) {
	fseek(file, 0, SEEK_END);
	int t = ftell(file);
	rewind(file);

	return t;
}

void construct_ustar_header(FILE_HEADER* fh, FILE* file) {
	fread(fh->name, NAME_S, 1, file);
	fread(fh->mode, MODE_S, 1, file);
	fread(fh->uid, UID_S, 1, file);
	fread(fh->gid, GID_S, 1, file);
	fread(fh->size, SIZE_S, 1, file);
	fread(fh->atime, ATIME_S, 1, file);
	fread(fh->cksum, CKSUM_S, 1, file);
	fread(fh->typeflag, TYPEFLAG_S, 1, file);
	fread(fh->linkname, LINKNAME_S, 1, file);
	fread(fh->magic, MAGIC_S, 1, file);
	fread(fh->version, VERSION_S, 1, file);
	fread(fh->uname, UNAME_S, 1, file);
	fread(fh->gname, GNAME_S, 1, file);
	fread(fh->devmajor, DEVMAJOR_S, 1, file);
	fread(fh->devminor, DEVMINOR_S, 1, file);
	fread(fh->prefix, PREFIX_S, 1, file);
	fread(fh->stuffing, STUFFING_S, 1, file);
}

void extract_files_from_archive(FILE * archive) {
	struct stat buf;
	FILE_HEADER fh;
	int i;
	int it;
	bool end_of_archive = false;

	construct_ustar_header(&fh, archive);

	do {
		if(fh.name != NULL && fh.name[0] != 0) {
			// Get size and create output file
			size_t filesize = oct2dec(fh.size);
			FILE* output_file = fopen(fh.name, "w+");

			if(output_file != NULL) {
				i = 0;
				it = filesize / BLOC_SIZE;

				if(it >= 0 && (filesize % BLOC_SIZE) > 0)
					it++;

				// Get the content from the archive
				while(i < (HEADER_S * it)) {
					if(i >= filesize)
						fgetc(archive);
					else
						fputc(fgetc(archive), output_file);
					
					i++;
				}

				fclose(output_file);
				output_file = NULL;
			}
			else
				fprintf(stderr, "Impossible d'extraire le fichier %s\n", fh.name);

			construct_ustar_header(&fh, archive);
		}
		else
			end_of_archive = true;
	} while(!end_of_archive);
}

void archive_reader(FILE * archive) {
	struct stat buf;
	FILE_HEADER fh;

	construct_ustar_header(&fh, archive);
	printf_header(fh);
}