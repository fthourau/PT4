#ifndef ARCHIVE_H
#define ARCHIVE_H

void build_or_add_archive_from_files(int number_of_arguments, char** files);
void list_files_from_archive(char* archive_path);
void add_files_to_archive(int number_of_arguments, char** files);

#endif