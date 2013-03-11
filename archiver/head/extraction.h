#ifndef _EXTRACTION_H_
#define _EXTRACTION_H_

#include <stdio.h>

void extract_files_from_archive(char* archive_path);
void extract_part_of_archive(int from, FILE* archive, char* path);

#endif