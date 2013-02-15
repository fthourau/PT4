#include "../head/ustarheader.h"
#include "../head/filehandling.h"

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void build_ustar_header_from_archive(FILE_HEADER* fh, FILE* file) {
	fread(fh->name, NAME_S, 1, file);
	fread(fh->mode, MODE_S, 1, file);
	fread(fh->uid, UID_S, 1, file);
	fread(fh->gid, GID_S, 1, file);
	fread(fh->size, SIZE_S, 1, file);
	fread(fh->mtime, MTIME_S, 1, file);
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

void build_ustar_header_from_file(FILE_HEADER* fh, char* filename) {
	struct stat buffer;

	if(stat(filename, &buffer) == 0) {
		get_prefix_and_name(filename, fh->name, fh->prefix);
		file_mode_edit(fh->mode, buffer.st_mode);
		get_id(fh->uid, buffer.st_uid);
		get_id(fh->gid, buffer.st_gid);
		get_size(fh->size, buffer.st_size);
		printf("%s\n", fh->name);
		printf("%s\n", fh->mode);
		printf("%s\n", fh->uid);
		printf("%s\n", fh->gid);
		printf("%s\n", fh->size);
		printf("%s\n", fh->prefix);
	}
	else
		fprintf(stderr, "Echec de stat sur le fichier %s.\n", filename);
}

void printf_header(FILE_HEADER fh) {
	printf("NAME: %s\n", fh.name);
	printf("MODE: %s\n", fh.mode);
	printf("UID: %s\n", fh.uid);
	printf("GID: %s\n", fh.gid);
	// printf("SIZE: %d\n", oct2dec(fh.size));		// Converted to decimal number
	printf("SIZE: %s\n", fh.size);
	printf("MTIME: %s\n", fh.mtime);
	printf("CKSUM: %s\n", fh.cksum);
	printf("TYPEFLAG: %s\n", fh.typeflag);
	printf("LINKNAME: %s\n", fh.linkname);
	printf("MAGIC: %s\n", fh.magic);
	printf("VERSION: %s\n", fh.version);
	printf("UNAME: %s\n", fh.uname);
	printf("GNAME: %s\n", fh.gname);
	printf("DEVMAJOR: %s\n", fh.devmajor);
	printf("DEVMINOR: %s\n", fh.devminor);
	printf("PREFIX: %s\n", fh.prefix);
	printf("STUFFING: %s\n", fh.stuffing);
}
