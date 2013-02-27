#ifndef _UTILITARIAN_H_
#define _UTILITARIAN_H_

#include <stdio.h>
#include <stdbool.h>

unsigned long long int oct2dec(char* n);
unsigned long long int dec2oct(char* n);
char* argument(int nb);
int get_file_weight(FILE* file);
bool is_tar_format(char* archive_to_check);
int position(char** files);
// Compression
void compress_with_gzip(char* filename);

#endif