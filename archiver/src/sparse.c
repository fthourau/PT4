#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>

#include "../head/sparse.h"
#include "../head/options.h"

void sparse_file(int number_of_argument, char** files) {
	int i = first_argument_position + 1;
	errno = 0;

	do {
		FILE* file = fopen(files[i], "r");

		if(file != NULL && errno == 0) {
			char c;
			size_t count = 0;
			size_t position = 0;
			
			SPARSE_HEADER header;
			initiate_header(&header);

			while( (c = fgetc(file)) != EOF) {
				if(c == '\0') {
					if(count == 0)
						position = ftell(file) - 1;
					count++;
				}
				else {
					if(count >= 20)
						append_to_header(&header, position, count);
					count = 0;
				}
			}
			printf("HEADER = %s%s%s\n", header.start, header.body, header.end);
			printf("LENGTH = %ld\n", header.length);
		}
		i++;
	} while(i < number_of_argument);
}

void initiate_header(SPARSE_HEADER* header) {
	header->length = DEFAULT_LENGTH;
	memset(header->start, 0, BODY_MAX_SIZE);
	memset(header->body, 0, BODY_MAX_SIZE);
	memset(header->end, 0, BODY_MAX_SIZE);
	strcat(header->start, "@@sparse[");
	strcat(header->end, "]@@");
}

void append_to_header(SPARSE_HEADER* header, int pos, int number) {
	char* buffer = malloc(100);

	sprintf(buffer, "%d;%d;", pos, number);

	strcat(header->body, buffer);
	header->length += strlen(buffer);

	free(buffer);
	buffer = NULL;
}