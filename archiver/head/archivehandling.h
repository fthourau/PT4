#ifndef ARCHIVEHANDLING_H
#define ARCHIVEHANDLING_H

#include <stdio.h>

#define BLOCK_SIZE 512

unsigned int calculate_number_of_block(size_t filesize);
int file_is_present(char* filename, char* prefix, FILE* archive);

#endif