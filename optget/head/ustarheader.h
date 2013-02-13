#ifndef _USTARHEADER_H_
#define _USTARHEADER_H_

#include <stdio.h>

// CONSTANT SIZES OF USTAR HEADER FIELDS
#define NAME_S 100
#define MODE_S 8
#define UID_S 8
#define GID_S 8
#define SIZE_S 12
#define MTIME_S 12
#define CKSUM_S 8
#define TYPEFLAG_S 1
#define LINKNAME_S 100
#define MAGIC_S 6
#define VERSION_S 2
#define UNAME_S 32
#define GNAME_S 32
#define DEVMAJOR_S 8
#define DEVMINOR_S 8
#define PREFIX_S 155
#define STUFFING_S 12
#define HEADER_S 512

// STRUCTURE OF A FILE'S HEADER IN *.TAR ARCHIVE
typedef struct FILE_HEADER {
	char name[NAME_S];				// Name of the file
	char mode[MODE_S];				// File permissions
	char uid[UID_S];				// User IDentifier
	char gid[GID_S];				// Group IDentifier
	char size[SIZE_S];				// Lengh of file contents
	char mtime[MTIME_S];			// Last modification time
	char cksum[CKSUM_S];			// File and header checksum
	char typeflag[TYPEFLAG_S];		// Type of the file
	char linkname[LINKNAME_S];		// Name uses for the link
	char magic[MAGIC_S];			// Is equal to string "USTAR"
	char version[VERSION_S];		// Version of the tar command used
	char uname[UNAME_S];			// Name of owner (ASCII)
	char gname[GNAME_S];			// Name of group (ASCII)
	char devmajor[DEVMAJOR_S];		// DEVice MAJOR number
	char devminor[DEVMINOR_S];		// DEVice MINOR number
	char prefix[PREFIX_S];			// Used to create file's path if non-null
	char stuffing[STUFFING_S];		// Stuffing bytes
} FILE_HEADER;

// SOME UTILITARIAN FUNCTIONS
void construct_ustar_header_from_archive(FILE_HEADER* fh, FILE* archive);
void construct_ustar_header_from_file(FILE_HEADER* fh, char* filename);

void printf_header(FILE_HEADER fh);

#endif