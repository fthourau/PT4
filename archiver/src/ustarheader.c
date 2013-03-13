#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include "../head/ustarheader.h"
#include "../head/filehandling.h"
#include "../head/utilitarian.h"
#include "../head/errors.h"

// Prototypes of private functions
void clean_up_header(FILE_HEADER* header);

void build_ustar_header_from_archive(FILE_HEADER* header, FILE* file) {
	clean_up_header(header);

	fread(header->name, NAME_S, 1, file);
	fread(header->mode, MODE_S, 1, file);
	fread(header->uid, UID_S, 1, file);
	fread(header->gid, GID_S, 1, file);
	fread(header->size, SIZE_S, 1, file);
	fread(header->mtime, MTIME_S, 1, file);
	fread(header->cksum, CKSUM_S, 1, file);
	fread(header->typeflag, TYPEFLAG_S, 1, file);
	fread(header->linkname, LINKNAME_S, 1, file);
	fread(header->magic, MAGIC_S, 1, file);
	fread(header->version, VERSION_S, 1, file);
	fread(header->uname, UNAME_S, 1, file);
	fread(header->gname, GNAME_S, 1, file);
	fread(header->devmajor, DEVMAJOR_S, 1, file);
	fread(header->devminor, DEVMINOR_S, 1, file);
	fread(header->prefix, PREFIX_S, 1, file);
	fread(header->stuffing, STUFFING_S, 1, file);
}

void build_ustar_header_from_file(FILE_HEADER* header, char* filename) {
	struct stat buffer;
	errno = 0;

	if(stat(filename, &buffer) == 0 && errno == 0) {
		clean_up_header(header);

		get_prefix_and_name(filename, header->name, header->prefix);
		get_file_mode(header->mode, buffer.st_mode);
		get_id(header->uid, buffer.st_uid);
		get_id(header->gid, buffer.st_gid);
		get_size(header->size, buffer.st_size);
		get_modification_time(header->mtime, buffer.st_mtime);
		get_file_type(header->typeflag, buffer.st_mode);
		strcpy(header->magic, "ustar ");
		strcpy(header->version, " \0");
		get_username(header->uname, buffer.st_uid);
		get_groupname(header->gname, buffer.st_gid);
		get_device_numbers(header->devmajor, header->devminor, buffer.st_dev);
		calculate_checksum(header);
	}
	else
		fprintf(stderr, "%s '%s': %s\n", STAT_FAILURE_ERR, filename,
															strerror(errno));
}

void write_header_to_archive(FILE_HEADER* header, FILE* archive) {
	fwrite(header->name, NAME_S, 1, archive);
	fwrite(header->mode, MODE_S, 1, archive);
	fwrite(header->uid, UID_S, 1, archive);
	fwrite(header->gid, GID_S, 1, archive);
	fwrite(header->size, SIZE_S, 1, archive);
	fwrite(header->mtime, MTIME_S, 1, archive);
	fwrite(header->cksum, CKSUM_S, 1, archive);
	fwrite(header->typeflag, TYPEFLAG_S, 1, archive);
	fwrite(header->linkname, LINKNAME_S, 1, archive);
	fwrite(header->magic, MAGIC_S, 1, archive);
	fwrite(header->version, VERSION_S, 1, archive);
	fwrite(header->uname, UNAME_S, 1, archive);
	fwrite(header->gname, GNAME_S, 1, archive);
	fwrite(header->devmajor, DEVMAJOR_S, 1, archive);
	fwrite(header->devminor, DEVMINOR_S, 1, archive);
	fwrite(header->prefix, PREFIX_S, 1, archive);
	fwrite(header->stuffing, STUFFING_S, 1, archive);
}

void calculate_checksum(FILE_HEADER* header) {
	int sum = 0;
	char buffer[8];

	int unit[15] = {
		NAME_S, MODE_S, UID_S, GID_S, SIZE_S, MTIME_S, TYPEFLAG_S, LINKNAME_S,
		MAGIC_S, VERSION_S, UNAME_S, GNAME_S, DEVMAJOR_S, DEVMINOR_S, PREFIX_S
	};

	int i;
	int j = -1;

loop:
	i = 0;
	j++;

	while(i < unit[j]) {
		switch(j) {
			case 0:
				sum += (int)header->name[i++];
			break;
			case 1:
				sum += (int)header->mode[i++];
			break;
			case 2:
				sum += (int)header->uid[i++];
			break;
			case 3:
				sum += (int)header->gid[i++];
			break;
			case 4:
				sum += (int)header->size[i++];
			break;
			case 5:
				sum += (int)header->mtime[i++];
			break;
			case 6:
				sum += (int)header->typeflag[i++];
			break;
			case 7:
				sum += (int)header->linkname[i++];
			break;
			case 8:
				sum += (int)header->magic[i++];
			break;
			case 9:
				sum += (int)header->version[i++];
			break;
			case 10:
				sum += (int)header->uname[i++];
			break;
			case 11:
				sum += (int)header->gname[i++];
			break;
			case 12:
				sum += (int)header->devmajor[i++];
			break;
			case 13:
				sum += (int)header->devminor[i++];
			break;
			case 14:
				sum += (int)header->prefix[i++];
			break;
		}
	}
		
	if(j != 14)
		goto loop;

	sprintf(buffer, "%d", sum);
	sprintf(buffer, "%lld", dec2oct(buffer));

	header->cksum[0] = '0';
	header->cksum[1] = buffer[0];
	header->cksum[2] = buffer[1];
	header->cksum[3] = buffer[2];
	header->cksum[4] = buffer[3];
	header->cksum[5] = buffer[4];
	header->cksum[6] = '\0';
	header->cksum[7] = ' ';
}

void printf_header(FILE_HEADER* header) {
	printf("%s", header->name);
	printf("%s", header->mode);
	printf("%s", header->uid);
	printf("%s", header->gid);
	printf("%s", header->size);
	printf("%s", header->mtime);
	printf("%s", header->cksum);
	printf("%s", header->typeflag);
	printf("%s", header->linkname);
	printf("%s", header->magic);
	printf("%s", header->version);
	printf("%s", header->uname);
	printf("%s", header->gname);
	printf("%s", header->devmajor);
	printf("%s", header->devminor);
	printf("%s", header->prefix);
	printf("%s", header->stuffing);
}

void printf_header_info(FILE_HEADER* header) {
	if(header->typeflag[0] == '5')
		printf("d");
	else if(header->typeflag[0] == '1')
		printf("l");
	else
		printf("-");

    printf("%s", get_rights(header->mode[4]));
    printf("%s", get_rights(header->mode[5]));
    printf("%s", get_rights(header->mode[6]));
    printf(" %s %s ", header->uname, header->gname);
    printf("%s ", get_weight(oct2dec(header->size)));
    // The following expression permits to cut the final '\n' character
    printf("%.*s%s", 24, get_asc_date(oct2dec(header->mtime)), 
    					&get_asc_date(oct2dec(header->mtime))[25]);
    printf(" %s\n", header->name);
}

// Private functions

void clean_up_header(FILE_HEADER* header) {
	fulfill_empty_space(header->name, 0, NAME_S);
	fulfill_empty_space(header->mode, 0, MODE_S);
	fulfill_empty_space(header->uid, 0, UID_S);
	fulfill_empty_space(header->gid, 0, GID_S);
	fulfill_empty_space(header->size, 0, SIZE_S);
	fulfill_empty_space(header->mtime, 0, MTIME_S);
	fulfill_empty_space(header->cksum, 0, CKSUM_S);
	fulfill_empty_space(header->typeflag, 0, TYPEFLAG_S);
	fulfill_empty_space(header->linkname, 0, LINKNAME_S);
	fulfill_empty_space(header->magic, 0, MAGIC_S);
	fulfill_empty_space(header->version, 0, VERSION_S);
	fulfill_empty_space(header->uname, 0, UNAME_S);
	fulfill_empty_space(header->gname, 0, GNAME_S);
	fulfill_empty_space(header->devmajor, 0, DEVMAJOR_S);
	fulfill_empty_space(header->devminor, 0, DEVMINOR_S);
	fulfill_empty_space(header->prefix, 0, PREFIX_S);
	fulfill_empty_space(header->stuffing, 0, STUFFING_S);
}