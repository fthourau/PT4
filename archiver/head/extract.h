#ifndef EXTRACT_H
#define EXTRACT_H

#include <stdio.h>

void extract_files_from_archive(char* archive_path);
void extract_part_of_archive(int from, FILE* archive, char* path);

#endif /* EXTRACT_H */