#include <string.h>
#include <errno.h>

#include "../head/ustarheader.h"
#include "../head/options.h"
#include "../head/errors.h"

void delete_files_from_archive(int argc,char** files) {
	FILE* archive = fopen(files[first_argument_position], "r");
	int i = first_argument_position + 1;

	if(archive != NULL && errno == 0) {
		
	}
	else
		fprintf(stderr, "%s '%s': %s\n", INVALID_FILE_ERR,
							files[first_argument_position], strerror(errno));
}