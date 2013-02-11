#include <stdlib.h>
#include <stdio.h>

#include "../head/archive.h"

int main(int argc, char** argv) {
	FILE* archive = NULL;

	if(argc > 1)
		archive = fopen(argv[1], "r");
	else
		fprintf(stderr, "Argument manquant: <filename>\n");

	if(archive != NULL) {
		// extract_files_from_archive(archive);
		list_files_from_archive(archive);
		fclose(archive);
	}
	else
		fprintf(stderr, "Invalid file: %s\n", argv[1]);

	return EXIT_SUCCESS;
}