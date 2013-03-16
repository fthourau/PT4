#include <errno.h>
#include <string.h>

#include "../head/archivehandling.h"
#include "../head/errors.h"
#include "../head/options.h"
#include "../head/ustarheader.h"
#include "../head/utilitarian.h"

void list_files_from_archive(char* archive_path) {
	errno = 0;
	FILE* archive = fopen(archive_path, "r");

	if(archive != NULL && errno == 0) {
		if(VERBOSE_FLAG)
			printf("Listage du contenu de '%s':\n", archive_path);

		FILE_HEADER header;
		unsigned int cursor_offset, nbr_of_block;
		bool end_of_archive = false;

		build_ustar_header_from_archive(&header, archive);

		do {
			if(header.name != NULL && (int)header.name[0] > 32) {
				int filesize = oct2dec(header.size);

				if(VERBOSE_FLAG)
					printf_header_info(&header);
				else
					printf("%s%s\n", header.prefix, header.name);

				// Figuring out number of file content's block for the offset
				nbr_of_block = calculate_number_of_block(filesize);

				cursor_offset = (BLOCK_SIZE * nbr_of_block);

				// Applying offset to the file from the current cursor position
				fseek(archive, cursor_offset, SEEK_CUR);

				// Then, get the next header
				build_ustar_header_from_archive(&header, archive);
			}
			else
				end_of_archive = true;
		} while(!end_of_archive);
	}
	else {
		fprintf(stderr, "%s '%s': %s\n", INVALID_FILE_ERR, archive_path,
															strerror(errno));
	}
}