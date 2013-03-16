#ifndef ADD_H
#define ADD_H

#include <stdio.h>

#include "../head/ustarheader.h"

void add_files_to_archive(int number_of_argument, char** files);
void add_file(FILE_HEADER* header, FILE* file, FILE* archive);

#endif