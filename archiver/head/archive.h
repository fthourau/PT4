#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#define BLOCK_SIZE 512

void build_archive_from_files(int number_of_arguments, char** files);
void list_files_from_archive(char* archive_path);
void add_files_to_archive(int number_of_arguments, char** files);

#endif