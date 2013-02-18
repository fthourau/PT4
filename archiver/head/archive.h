#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#define BLOCK_SIZE 512

void extract_files_from_archive(char* archive_path);
void build_archive_from_files(int number_of_arguments, char** files);
void list_files_from_archive(char* archive_path);

#endif