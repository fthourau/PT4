#ifndef DELETE_H
#define DELETE_H

#include <stdio.h>

void delete_files_from_archive(int argc, char** files);
void delete_file(int file_position, FILE* archive, char* archive_name);

#endif