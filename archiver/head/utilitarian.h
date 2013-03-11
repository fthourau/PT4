#ifndef UTILITARIAN_H
#define UTILITARIAN_H

#include <stdio.h>
#include <stdbool.h>

unsigned long long int oct2dec(char* n);
unsigned long long int dec2oct(char* n);

int get_file_weight(FILE* file);
char* get_rights(char single_right_number);
char* get_weight(unsigned long long int weight);
char* get_asc_date(long int epoch_time);

// Format checking
bool is_tar_format(char* archive_to_check);
bool is_gzip_format(char* archive_to_check);

// Compression
void compress_with_gzip(char* filename);
void decompress_with_gzip(char* filename);

#endif