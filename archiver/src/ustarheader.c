#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

#include <stdio.h>
#include <time.h>

void printf_header(FILE_HEADER fh) {
	//time_t* mtime = (time_t*)fh.mtime;
	//time(mtime);

	printf("NAME: %s\n", fh.name);
	printf("MODE: %s\n", fh.mode);
	printf("UID: %s\n", fh.uid);
	printf("GID: %s\n", fh.gid);
	printf("SIZE: %d\n", oct2dec(fh.size));			// Converted to decimal number
	//printf("MTIME: %s", fh.mtime); 					// asctime(localtime(mtime))
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

int header_is_empty(FILE_HEADER fh) {
	if(atoi(fh.size) == 0) {
		return 1;
	}
	else return 0;
}


/* 
	&& fh.mode == '\0' && fh.uid == '\0' && fh.gid == '\0' &&
	fh.size == '\0' && fh.mtime == '\0' && fh.cksum == '\0' &&
	fh.typeflag == '\0' && fh.linkname == '\0' && fh.magic == '\0' &&
	fh.version == '\0' && fh.uname == '\0' && fh.gname == '\0' &&
	fh.devmajor == '\0' && fh.devminor == '\0' && fh.prefix == '\0'
*/