#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <fcntl.h>

#include "../head/archive.h"
#include "../head/options.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

void get_file_info_verbose(FILE_HEADER fh) {
	/*printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");*/
}

int get_file_weight(FILE* file) {
	fseek(file, 0, SEEK_END);
	int t = ftell(file);
	rewind(file);

	return t;
}

void extract_files_from_archive(FILE* archive) {
	FILE_HEADER fh;
	unsigned int cursor_pos, nbr_of_block;
	bool end_of_archive = false;

	if(VERBOSE_FLAG)
		printf("Retrieval in progress ...\n");

	build_ustar_header_from_archive(&fh, archive);

	do {
		if(fh.name != NULL && fh.name[0] != 0) {
			// Get size and create output file
			size_t filesize = oct2dec(fh.size);
			FILE* output_file = fopen(fh.name, "w+");

			if(output_file != NULL) {
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
					printf("Extracted: %s\n", fh.name);

				fclose(output_file);
				output_file = NULL;
			}
			else
				fprintf(stderr, "Impossible d'extraire le fichier %s\n", fh.name);

			build_ustar_header_from_archive(&fh, archive);
		}
		else
			end_of_archive = true;
	} while(!end_of_archive);
}

void build_archive_from_files(char* files[], char* archive_name) {
	FILE_HEADER fh;

	FILE* a = fopen("a.tar", "r");
	
	// if(FILENAME_FLAG)
		// archive_name = files[]

	if(VERBOSE_FLAG)
		printf("VERBOSE IS ACTIVE...\n");

	// build_ustar_header_from_archive(&fh, a);
	// printf_header(fh);
	build_ustar_header_from_file(&fh, files[1]);
}

void list_files_from_archive(FILE* archive) {
	FILE_HEADER fh;
	unsigned int cursor_offset;
	unsigned int nbr_of_block;
	bool end_of_archive = false;

	build_ustar_header_from_archive(&fh, archive);

	do {
		if(fh.name != NULL && fh.name[0] != 0) {
			int filesize = oct2dec(fh.size);

			if(VERBOSE_FLAG)
				get_file_info_verbose(fh);
			else
				printf("%s/%s\n", fh.prefix, fh.name);

			// Figuring out number of file content's block for the offset
			nbr_of_block = filesize / BLOCK_SIZE;

			if((filesize % BLOCK_SIZE) > 0)
				nbr_of_block++;

			cursor_offset = (BLOCK_SIZE * nbr_of_block);

			// Applying offset to the file from the current cursor position
			fseek(archive, cursor_offset, SEEK_CUR);

			// Then, get the next header
			build_ustar_header_from_archive(&fh, archive);
		}
		else
			end_of_archive = true;
	} while(!end_of_archive);
}