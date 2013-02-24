#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#define BLOCK_SIZE 512

void build_or_add_archive_from_files(int number_of_arguments, char** files, int type);
void list_files_from_archive(char* archive_path);

#endif