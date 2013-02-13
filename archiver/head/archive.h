#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#define BLOCK_SIZE 512

void extract_files_from_archive(FILE * archive);
void build_archive_from_files(char* files[], char* archive_name);
void list_files_from_archive(FILE * archive);

#endif