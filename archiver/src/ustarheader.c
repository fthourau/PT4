#include "../head/filehandling.h"

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


// Prototypes of private functions
void printf_header(FILE_HEADER* fh);
void clean_up_header(FILE_HEADER* header);

void build_ustar_header_from_archive(FILE_HEADER* header, FILE* file) {
	clean_up_header(header);

	fread(header->name, NAME_S, 1, file);
	fread(header->mode, MODE_S, 1, file);
	fread(header->uid, UID_S, 1, file);
	fread(header->gid, GID_S, 1, file);
	fread(header->size, SIZE_S, 1, file);
	fread(header->mtime, MTIME_S, 1, file);
	fread(header->cksum, CKSUM_S, 1, file);
	fread(header->typeflag, TYPEFLAG_S, 1, file);
	fread(header->linkname, LINKNAME_S, 1, file);
	fread(header->magic, MAGIC_S, 1, file);
	fread(header->version, VERSION_S, 1, file);
	fread(header->uname, UNAME_S, 1, file);
	fread(header->gname, GNAME_S, 1, file);
	fread(header->devmajor, DEVMAJOR_S, 1, file);
	fread(header->devminor, DEVMINOR_S, 1, file);
	fread(header->prefix, PREFIX_S, 1, file);
	fread(header->stuffing, STUFFING_S, 1, file);
}

void build_ustar_header_from_file(FILE_HEADER* header, char* filename) {
	struct stat buffer;
	errno = 0;

	if(stat(filename, &buffer) == 0 && errno == 0) {
		clean_up_header(header);

		get_prefix_and_name(filename, header->name, header->prefix);
		get_file_mode(header->mode, buffer.st_mode);
		get_id(header->uid, buffer.st_uid);
		get_id(header->gid, buffer.st_gid);
		get_size(header->size, buffer.st_size);
		get_modification_time(header->mtime, buffer.st_mtime);
		get_file_type(header->typeflag, buffer.st_mode);
		strcpy(header->magic, "ustar ");
		strcpy(header->version, " \0");
		get_username(header->uname, buffer.st_uid);
		get_groupname(header->gname, buffer.st_gid);
		get_device_numbers(header->devmajor, header->devminor, buffer.st_dev);
		calculate_checksum(header);
	}
	else
		fprintf(stderr, "Echec de stat sur le fichier '%s': %s\n", filename,
															strerror(errno));
}

void write_header_to_archive(FILE_HEADER* header, FILE* archive) {
	fwrite(header->name, NAME_S, 1, archive);
	fwrite(header->mode, MODE_S, 1, archive);
	fwrite(header->uid, UID_S, 1, archive);
	fwrite(header->gid, GID_S, 1, archive);
	fwrite(header->size, SIZE_S, 1, archive);
	fwrite(header->mtime, MTIME_S, 1, archive);
	fwrite(header->cksum, CKSUM_S, 1, archive);
	fwrite(header->typeflag, TYPEFLAG_S, 1, archive);
	fwrite(header->linkname, LINKNAME_S, 1, archive);
	fwrite(header->magic, MAGIC_S, 1, archive);
	fwrite(header->version, VERSION_S, 1, archive);
	fwrite(header->uname, UNAME_S, 1, archive);
	fwrite(header->gname, GNAME_S, 1, archive);
	fwrite(header->devmajor, DEVMAJOR_S, 1, archive);
	fwrite(header->devminor, DEVMINOR_S, 1, archive);
	fwrite(header->prefix, PREFIX_S, 1, archive);
	fwrite(header->stuffing, STUFFING_S, 1, archive);
}

// Private functions

void printf_header(FILE_HEADER* header) {
	printf("NAME: %s\n", header->name);
	printf("MODE: %s\n", header->mode);
	printf("UID: %s\n", header->uid);
	printf("GID: %s\n", header->gid);
	printf("SIZE: %s\n", header->size);
	printf("MTIME: %s\n", header->mtime);
	printf("CKSUM: %s\n", header->cksum);
	printf("TYPEFLAG: %s\n", header->typeflag);
	printf("LINKNAME: %s\n", header->linkname);
	printf("MAGIC: %s\n", header->magic);
	printf("VERSION: %s\n", header->version);
	printf("UNAME: %s\n", header->uname);
	printf("GNAME: %s\n", header->gname);
	printf("DEVMAJOR: %s\n", header->devmajor);
	printf("DEVMINOR: %s\n", header->devminor);
	printf("PREFIX: %s\n", header->prefix);
	printf("STUFFING: %s\n", header->stuffing);
}

void clean_up_header(FILE_HEADER* header) {
	fulfill_empty_space(header->name, 0, NAME_S);
	fulfill_empty_space(header->mode, 0, MODE_S);
	fulfill_empty_space(header->uid, 0, UID_S);
	fulfill_empty_space(header->gid, 0, GID_S);
	fulfill_empty_space(header->size, 0, SIZE_S);
	fulfill_empty_space(header->mtime, 0, MTIME_S);
	fulfill_empty_space(header->cksum, 0, CKSUM_S);
	fulfill_empty_space(header->typeflag, 0, TYPEFLAG_S);
	fulfill_empty_space(header->linkname, 0, LINKNAME_S);
	fulfill_empty_space(header->magic, 0, MAGIC_S);
	fulfill_empty_space(header->version, 0, VERSION_S);
	fulfill_empty_space(header->uname, 0, UNAME_S);
	fulfill_empty_space(header->gname, 0, GNAME_S);
	fulfill_empty_space(header->devmajor, 0, DEVMAJOR_S);
	fulfill_empty_space(header->devminor, 0, DEVMINOR_S);
	fulfill_empty_space(header->prefix, 0, PREFIX_S);
	fulfill_empty_space(header->stuffing, 0, STUFFING_S);
}