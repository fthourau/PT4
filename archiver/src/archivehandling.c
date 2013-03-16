#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "../head/archivehandling.h"
#include "../head/filehandling.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

// This function calculates the number of 512 bytes block according to the
// filesize
unsigned int calculate_number_of_block(size_t filesize) {
	unsigned int nbr_of_block = filesize / BLOCK_SIZE;

	if((filesize % BLOCK_SIZE) > 0)
		nbr_of_block++;

	return nbr_of_block;
}

// Research if a file named "prefix/filename" is present inside the archive
// If it's present, return the position of the cursor just before the header
// otherwise returns -1
int file_is_present(char* filename, char* prefix, FILE* archive) {
	bool end_of_archive = false;
	FILE_HEADER header;
	size_t filesize;
	unsigned int cursor_pos = -1;
	unsigned int cursor_offset, nbr_of_block;

	do {
		build_ustar_header_from_archive(&header, archive);

		if(header.name != NULL && (int)header.name[0] > 32) {
			if(strcmp(header.name, filename) == 0 && 
				strcmp(header.prefix, prefix) == 0) {
				cursor_pos = ftell(archive) - HEADER_S;
				end_of_archive = true;
			}
			else {
				filesize = oct2dec(header.size);
				nbr_of_block = calculate_number_of_block(filesize);
				cursor_offset = (BLOCK_SIZE *  nbr_of_block);
				fseek(archive, cursor_offset, SEEK_CUR);
			}
		}
		else
			end_of_archive = true;
	} while(!end_of_archive);

	rewind(archive);

	return cursor_pos;
}

unsigned int number_of_file_in_archive(FILE* archive) {
	bool end_of_archive = false;
	FILE_HEADER header;
	size_t filesize;
	unsigned int number_of_file = 0;
	unsigned int cursor_offset, nbr_of_block;

	do {
		build_ustar_header_from_archive(&header, archive);

		if(header.name != NULL && (int)header.name[0] > 32) {
			number_of_file++;

			filesize = oct2dec(header.size);
			nbr_of_block = calculate_number_of_block(filesize);
			cursor_offset = (BLOCK_SIZE *  nbr_of_block);
			fseek(archive, cursor_offset, SEEK_CUR);
		}
		else
			end_of_archive = true;
	} while(!end_of_archive);

	rewind(archive);

	return number_of_file;
}

void complete_current_block(unsigned int from, unsigned int to, FILE* file) {
	unsigned int missing_size = to - from;
	char* block = malloc(missing_size);
	memset(block, 0, missing_size);
	fwrite(block, missing_size, 1, file);

	free(block);
	block = NULL;
}

void write_null_block(FILE* archive) {
	char* null_block = malloc(BLOCK_SIZE);
	memset(null_block, 0, BLOCK_SIZE);
	fwrite(null_block, BLOCK_SIZE, 1, archive);
	
	free(null_block);
	null_block = NULL;
}

void erase_ending_null_block(FILE* archive, char* archivename) {
	int archivesize = get_file_weight(archive);
	archivesize -= BLOCK_SIZE;
	char* buffer = malloc(archivesize);
	memset(buffer, 0, archivesize);
	fread(buffer, archivesize, 1, archive);

	fclose(archive);
	archive = NULL;

	char* commandline = malloc(256);
	memset(commandline, 0, 256);
	strcat(commandline, "rm -rf ");
	strcat(commandline, archivename);
	system(commandline);

	free(commandline);
	commandline = NULL;

	archive = fopen(archivename, "a");

	if(archive != NULL) {
		fwrite(buffer, archivesize, 1, archive);
	}

	free(buffer);
	buffer = NULL;
}