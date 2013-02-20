#include "../head/ustarheader.h"
#include "../head/filehandling.h"

#include <string.h>
#include <unistd.h>
#include <errno.h>
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
	errno = 0;

	if(stat(filename, &buffer) == 0 && errno == 0) {
		// It's preferable to clean fields with null-terminated
		fulfill_empty_space(fh->name, 0, NAME_S);
		fulfill_empty_space(fh->uid, 0, UID_S);
		fulfill_empty_space(fh->gid, 0, GID_S);
		fulfill_empty_space(fh->size, 0, SIZE_S);
		fulfill_empty_space(fh->mtime, 0, MTIME_S);
		fulfill_empty_space(fh->cksum, 0, CKSUM_S);
		fulfill_empty_space(fh->linkname, 0, LINKNAME_S);
		fulfill_empty_space(fh->uname, 0, UNAME_S);
		fulfill_empty_space(fh->gname, 0, GNAME_S);
		fulfill_empty_space(fh->devmajor, 0, DEVMAJOR_S);
		fulfill_empty_space(fh->devminor, 0, DEVMINOR_S);
		fulfill_empty_space(fh->prefix, 0, PREFIX_S);
		fulfill_empty_space(fh->stuffing, 0, STUFFING_S);

		get_prefix_and_name(filename, fh->name, fh->prefix);
		file_mode_edit(fh->mode, buffer.st_mode);
		get_id(fh->uid, buffer.st_uid);
		get_id(fh->gid, buffer.st_gid);
		get_size(fh->size, buffer.st_size);
		get_modification_time(fh->mtime, buffer.st_mtime);
		get_file_type(fh->typeflag, buffer.st_mode);
		strcpy(fh->magic, "ustar ");
		strcpy(fh->version, " \0");
		get_username(fh->uname, buffer.st_uid);
		get_groupname(fh->gname, buffer.st_gid);
		get_device_numbers(fh->devmajor, fh->devminor, buffer.st_dev);
		calculate_checksum(fh);
	}
	else
		fprintf(stderr, "Echec de stat sur le fichier '%s': %s\n", filename,
															strerror(errno));
}

void write_header_to_archive(FILE_HEADER* fh, FILE* archive) {
	fwrite(fh->name, NAME_S, 1, archive);
	fwrite(fh->mode, MODE_S, 1, archive);
	fwrite(fh->uid, UID_S, 1, archive);
	fwrite(fh->gid, GID_S, 1, archive);
	fwrite(fh->size, SIZE_S, 1, archive);
	fwrite(fh->mtime, MTIME_S, 1, archive);
	fwrite(fh->cksum, CKSUM_S, 1, archive);
	fwrite(fh->typeflag, TYPEFLAG_S, 1, archive);
	fwrite(fh->linkname, LINKNAME_S, 1, archive);
	fwrite(fh->magic, MAGIC_S, 1, archive);
	fwrite(fh->version, VERSION_S, 1, archive);
	fwrite(fh->uname, UNAME_S, 1, archive);
	fwrite(fh->gname, GNAME_S, 1, archive);
	fwrite(fh->devmajor, DEVMAJOR_S, 1, archive);
	fwrite(fh->devminor, DEVMINOR_S, 1, archive);
	fwrite(fh->prefix, PREFIX_S, 1, archive);
	fwrite(fh->stuffing, STUFFING_S, 1, archive);
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
