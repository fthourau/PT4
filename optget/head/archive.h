#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#define BLOCK_SIZE 512

//void archive_reader(char* filename);
void archive_reader(FILE * archive);
void extract_files_from_archive(FILE * archive);

#endif