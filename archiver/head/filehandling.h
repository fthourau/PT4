#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <sys/types.h>

void get_prefix_and_name(char* full_path, char* filename, char* path);
void get_file_mode(char* header_mode, mode_t stat_mode);
void get_id(char* header_id, int id);
void get_size(char* filesize, off_t size);
void get_modification_time(char* header_mtime, time_t mtime);
void get_file_type(char* type, mode_t mode);
void get_username(char* username, uid_t user_id);
void get_groupname(char* groupname, gid_t group_id);
void get_device_numbers(char* devmajor, char* devminor, dev_t devnumber);

// The function fulfills the string empty space with NULL-terminated character
void fulfill_empty_space(char* string, int starting_point, int length);

#endif