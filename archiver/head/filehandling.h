#ifndef _FILEHANDLING_H_
#define _FILEHANDLING_H_

#include <sys/types.h>

void get_prefix_and_name(char* full_path, char* filename, char* path);
void file_mode_edit(char* header_mode, mode_t stat_mode);
char get_user_mode(mode_t mode);
char get_group_mode(mode_t mode);
char get_other_mode(mode_t mode);
void get_id(char* header_id, int id);
void get_size(char* filesize, off_t size);

#endif