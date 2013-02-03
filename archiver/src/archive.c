#include "../head/archive.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

int get_file_weight(FILE* file) {
	fseek(file, 0, SEEK_END);
	int t = ftell(file);
	rewind(file);

	return t;
}

void construct_ustar_header(FILE_HEADER* fh, struct stat buf, FILE* file) {
	//int stats = stat("archive.tar", &buf);

	fread(fh->name, NAME_S, 1, file);
	fread(fh->mode, MODE_S, 1, file);
	fread(fh->uid, UID_S, 1, file);
	fread(fh->gid, GID_S, 1, file);
	fread(fh->size, SIZE_S, 1, file);
	fread(fh->atime, ATIME_S, 1, file);
	//fh->mtime = ctime(&buf.st_mtime);
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
}

void extract_files_from_archive(char* filename) {
	FILE* archive = fopen(filename, "r");
	unsigned int archive_size = get_file_weight(archive);

	while(archive_size != 0) {
		// Demander pourquoi devoir ajouter 12 au poids du fichier
		
		// USTAR header and stat
		struct stat buf;
		FILE_HEADER fh;
		construct_ustar_header(&fh, buf, archive);

		// Output file from the archive
		FILE* file = fopen(fh.name, "w");

		// Size of the file given by the header
		size_t filesize = oct2dec(fh.size) + 12;

		// Buffer of file's content
		char* content = malloc(filesize);
		
		// Get the content from the archive
		fread(content, filesize, 1, archive);

		// Fill up the output file from the buffer
		fwrite(content, filesize, 1, file);
		
		// Release buffer and close output file
		free(content);
		fclose(file);

		// Adjust remaining archive size
		archive_size -= (HEADER_S + filesize);
	}
}

void archive_reader(char* filename) {
	struct stat buf;
	FILE_HEADER fh;
	FILE *archive = fopen(filename, "r");

	construct_ustar_header(&fh, buf, archive);
	printf_header(fh);
	fclose(archive);
}