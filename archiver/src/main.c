#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#include "../head/utilitarian.h"
#include "../head/ustarheader.h"
#include "../head/options.h"
#include "../head/archive.h"

int main(int argc, char** argv) {
	FILE* archive = NULL;

	if(argc > 1)
		archive = fopen(argv[1], "r");
	else
		fprintf(stderr, "Argument manquant: <filename>\n");

	if(archive != NULL) {
		fclose(archive);
		//archive_reader(argv[1]);
		extract_files_from_archive(argv[1]);
	}
	else
		fprintf(stderr, "Invalid file: %s\n", argv[1]);

	return EXIT_SUCCESS;
}