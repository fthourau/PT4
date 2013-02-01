#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#include "ustarheader.h"
#include "utilitarian.h"

#define TAILLE 1000

int main(int argc, char** argv) {
	struct stat buf;
	FILE* fichier = fopen("archive.tar", "r");
	char l[TAILLE] = "";
	FILE_HEADER fh;

	if(fichier != NULL) {
		fseek(fichier, 0, SEEK_END);
		printf("Taille de l'archive: %ld\n", ftell(fichier));
		rewind(fichier);

		int stats = stat("archive.tar", &buf);
		//printf( "Time accessed : %s", ctime( &buf.st_atime ) );
      	//printf( "Time modified : %s", ctime( &buf.st_mtime ) );
/*
		fread(fh.name, NAME_S, 1, fichier);
		fread(fh.mode, MODE_S, 1, fichier);
		fread(fh.uid, UID_S, 1, fichier);
		fread(fh.gid, GID_S, 1, fichier);
		fread(fh.size, SIZE_S, 1, fichier);
		fread(fh.atime, ATIME_S, 1, fichier);
		fh.mtime = ctime(&buf.st_mtime);
		fread(fh.cksum, CKSUM_S, 1, fichier);
		fread(fh.typeflag, TYPEFLAG_S, 1, fichier);
		fread(fh.linkname, LINKNAME_S, 1, fichier);
		fread(fh.magic, MAGIC_S, 1, fichier);
		fread(fh.version, VERSION_S, 1, fichier);
		fread(fh.uname, UNAME_S, 1, fichier);
		fread(fh.gname, GNAME_S, 1, fichier);
		fread(fh.devmajor, DEVMAJOR_S, 1, fichier);
		fread(fh.devminor, DEVMINOR_S, 1, fichier);
		fread(fh.prefix, PREFIX_S, 1, fichier);

		printf_header(fh);*/
		char* dec = "7";
		printf("7 -> %d\n", oct2dec(dec));

		dec = "47";
		printf("47 -> %d\n", oct2dec(dec));

		dec = "477";
		printf("477 -> %d\n", oct2dec(dec));

		fclose(fichier);
	}

	return EXIT_SUCCESS;
}