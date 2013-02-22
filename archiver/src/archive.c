#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    // touch -d -> edit mtime
	// touch -d "`date -d @1360884899 '+%Y-%m-%d %H:%M:%S'`" <filename>
}

void build_archive_from_files(int number_of_arguments, char** files) {
	FILE_HEADER fh;
	FILE* archive = NULL;
	FILE* current_file = NULL;
	int i;
	unsigned int cursor_pos, nbr_of_block;
	size_t filesize;

	errno = 0;

	if(files[2] != NULL && is_tar_format(files[2])) {
		archive = fopen(files[2], "w");
		i = 3;
	}
	else {
		archive = fopen("archive.tar", "w");
		i = 2;
	}

	if(archive != NULL && errno == 0) {
		errno = 0;

		if(VERBOSE_FLAG && ARCHIVE_NAME_FLAG)
			printf("Creation of '%s' in progress ...\n", files[2]);
		else if(VERBOSE_FLAG)
			printf("Creation of 'archive.tar' in progress ...\n");

		do {
			current_file = fopen(files[i], "r");
			
			if(current_file != NULL && errno == 0) {
				build_ustar_header_from_file(&fh, files[i]);
				write_header_to_archive(&fh, archive);
				
				if(fh.typeflag[0] == '0') {	// Only if it's a regular file
					filesize = oct2dec(fh.size);

					cursor_pos = 0;
					nbr_of_block = filesize / BLOCK_SIZE;

					if((filesize % BLOCK_SIZE) > 0)
						nbr_of_block++;

					while(cursor_pos < (BLOCK_SIZE * nbr_of_block)) {
						if(cursor_pos >= filesize)
							fputc('\0', archive);
						else
							fputc(fgetc(current_file), archive);
						
						cursor_pos++;
					}
					fclose(current_file);
					current_file = NULL;
					fputc('\n', archive);
				}
				i++;
			}
			else
				fprintf(stderr, "Erreur d'ouverture de '%s': %s\n", 
										fh.name, strerror(errno));
		} while(i < number_of_arguments);

		for (int i = 0; i < BLOCK_SIZE; i++)
			fputc('\0', archive);

		fclose(archive);
		archive = NULL;
	}
	else {
		if(ARCHIVE_NAME_FLAG)
			fprintf(stderr, "Fichier invalide '%s': %s\n", files[2],
															strerror(errno));
		else
			fprintf(stderr, "Fichier invalide 'archive.tar': %s\n",
															strerror(errno));
	}
}

void list_files_from_archive(char* archive_path) {
	errno = 0;
	FILE* archive = fopen(archive_path, "r");

	if(archive != NULL && errno == 0) {
		if(VERBOSE_FLAG)
			printf("Listage du contenu de '%s':\n", archive_path);

		FILE_HEADER header;
		unsigned int cursor_offset;
		unsigned int nbr_of_block;
		bool end_of_archive = false;

		build_ustar_header_from_archive(&header, archive);

		do {
			if(header.name != NULL && header.name[0] != '\0') {
				int filesize = oct2dec(header.size);

				if(VERBOSE_FLAG)
					get_file_info_verbose(header);
				else {
					if(header.prefix != NULL && header.prefix[0] != 0)
						printf("%s/%s\n", header.prefix, header.name);
					else
						printf("%s\n", header.name);
				}

				// Figuring out number of file content's block for the offset
				nbr_of_block = filesize / BLOCK_SIZE;

				if((filesize % BLOCK_SIZE) > 0)
					nbr_of_block++;

				cursor_offset = (BLOCK_SIZE * nbr_of_block);

				// Applying offset to the file from the current cursor position
				fseek(archive, cursor_offset, SEEK_CUR);

				// Then, get the next header
				build_ustar_header_from_archive(&header, archive);
			}
			else
				end_of_archive = true;
		} while(!end_of_archive);
	}
	else
		fprintf(stderr, "Fichier invalide '%s': %s\n", 
											archive_path, strerror(errno));
}

void add_files_to_archive(int number_of_arguments, char** files) {

}