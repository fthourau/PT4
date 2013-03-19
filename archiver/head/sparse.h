#ifndef SPARSE_H
#define SPARSE_H

#define START_LENGTH 9
#define END_LENGTH 3
#define DEFAULT_LENGTH (START_LENGTH + END_LENGTH)
#define BODY_MAX_SIZE 2048

typedef struct SPARSE_HEADER {
	size_t length;
	char start[9];
	char body[BODY_MAX_SIZE];
	char end[3];
} SPARSE_HEADER;

// Some utilitarian functions concerning the structure
void initiate_header(SPARSE_HEADER* header);
void append_to_header(SPARSE_HEADER* header, int pos, int number);

void sparse_file(int number_of_argument, char** files);

#endif /* SPARSE_H */