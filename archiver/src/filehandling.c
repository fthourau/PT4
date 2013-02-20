#include "../head/filehandling.h"
#include "../head/utilitarian.h"

#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <sys/stat.h>
#include <linux/kdev_t.h>

void get_prefix_and_name(char* full_path, char* filename, char* path) {
	int length = strlen(full_path);
	int i, j;
	int last_but_one_separator_position = -1;
	int last_separator_position = -1;

	// This part is looking for a folder separator
	for(i = 0 ; i < length ; i++) {
		if(full_path[i] == '/') {
			last_but_one_separator_position = last_separator_position;
			last_separator_position = i;
		}
	}

	if( ( ( last_but_one_separator_position == -1 ||
			last_but_one_separator_position == 0 ) &&
		last_separator_position == (length - 1) ) ) {
		// This is when it's just a folder like '/dir/' or 'dir/'
		strcpy(filename, full_path);
	}
	else if(last_separator_position == -1) {
		// This is when it's just a file (everything except a directory)
		strcpy(filename, full_path);
	}
	else {
		j = 0;
		for(i = 0 ; i < length ; i++) {
			// The path is copied before
			// An empty directory
			if( last_separator_position == (length - 1) &&
				i <= last_but_one_separator_position ) {
				path[i] = full_path[i];
			}
			else if( last_separator_position != (length - 1) && 
					 i <= last_separator_position ) {
				// A file in a directory
				path[i] = full_path[i];
			}
			else {
				// Then, the filename is copied too
				filename[j] = full_path[i];
				j++;
			}
		}
	}
}

void file_mode_edit(char* header_mode, mode_t stat_mode) {
	header_mode[0] = '0';
	header_mode[1] = '0';
	header_mode[2] = '0';
	header_mode[3] = '0';
	header_mode[4] = get_user_mode(stat_mode);
	header_mode[5] = get_group_mode(stat_mode);
	header_mode[6] = get_other_mode(stat_mode);
	header_mode[7] = '\0';
}

char get_user_mode(mode_t mode) {
	char m = '0';
	int n = 0;

	if(mode & S_IRUSR) {
		m = '4';
		n += 4;
	}

	if(mode & S_IWUSR) {
		m = '2';
		n += 2;
	}

	if(mode & S_IXUSR) {
		m = '1';
		n++;
	}

	if(n != 4 && n != 2 && n != 1) {
		if(n == 7)			// rwx
			return '7';
		else if(n == 6)		// rw-
			return '6';
		else if(n == 5)		// r-x
			return '5';
		else if(n == 3)		// -wx
			return '3';
		else
			return '0';		// ---
	}
	else
		return m;			// r-- or -w- or --x
}

char get_group_mode(mode_t mode) {
	char m = '0';
	int n = 0;

	if(mode & S_IRGRP) {
		m = '4';
		n += 4;
	}

	if(mode & S_IWGRP) {
		m = '2';
		n += 2;
	}

	if(mode & S_IXGRP) {
		m = '1';
		n++;
	}

	if(n != 4 && n != 2 && n != 1) {
		if(n == 7)			// rwx
			return '7';
		else if(n == 6)		// rw-
			return '6';
		else if(n == 5)		// r-x
			return '5';
		else if(n == 3)		// -wx
			return '3';
		else
			return '0';		// ---
	}
	else
		return m;			// r-- or -w- or --x
}

char get_other_mode(mode_t mode) {
	char m = '0';
	int n = 0;

	if(mode & S_IROTH) {
		m = '4';
		n += 4;
	}

	if(mode & S_IWOTH) {
		m = '2';
		n += 2;
	}

	if(mode & S_IXOTH) {
		m = '1';
		n++;
	}

	if(n != 4 && n != 2 && n != 1) {
		if(n == 7)			// rwx
			return '7';
		else if(n == 6)		// rw-
			return '6';
		else if(n == 5)		// r-x
			return '5';
		else if(n == 3)		// -wx
			return '3';
		else
			return '0';		// ---
	}
	else
		return m;			// r-- or -w- or --x
}

void get_id(char* header_id, int id) {
	char buff[UID_S] = {0};
	sprintf(buff, "%d", id);
	id = dec2oct(buff);

	// UID/GID range is between 0 and 32767 so 2 first positions are always 0
	header_id[0] = '0';
	header_id[1] = '0';
	header_id[2] =  (char)( 48 + (id / 10000) );
	id -= (id / 10000) * 10000;
	header_id[3] =  (char)( 48 + (id / 1000) );
	id -= (id / 1000) * 1000;
	header_id[4] =  (char)( 48 + (id / 100) );
	id -= (id / 100) * 100;
	header_id[5] =  (char)( 48 + (id / 10) );
	id -= (id / 10) * 10;
	header_id[6] =  (char)( 48 + id );
	header_id[7] = '\0';
}

void get_size(char* filesize, off_t size) {
	char buffer[SIZE_S];
	int i = 0;
	
	fulfill_empty_space(buffer, 0, SIZE_S);

	sprintf(filesize, "%ld", size);
	sprintf(buffer, "%lld", dec2oct(filesize));
	
	int len = strlen(buffer);

	for(i = 0 ; i < (SIZE_S - 1); i++)
		filesize[i] = '0';

	i = 0;

	while(buffer[i] != '\0' && i < len) {
		filesize[SIZE_S - len - 1 + i] = buffer[i];
		i++;
	}
}

void get_modification_time(char* header_mtime, time_t mtime) {
	char buffer[MTIME_S];
	int i = 0;

	fulfill_empty_space(buffer, 0, MTIME_S);

	sprintf(header_mtime, "%ld", mtime);
	sprintf(buffer, "%lld", dec2oct(header_mtime));

	int len = strlen(buffer);

	for(i = 0 ; i < (MTIME_S - 1) ; i++)
		header_mtime[i] = '0';

	i = 0;

	while(buffer[i] != '\0') {
		header_mtime[MTIME_S - len - 1 + i] = buffer[i];
		i++;
	}
}

void get_file_type(char* type, mode_t mode) {
	if(S_ISREG(mode))
		type[0] = '0';
	else if(S_ISLNK(mode))
		type[0] = '1';
	else if(S_ISCHR(mode))
		type[0] = '3';
	else if(S_ISBLK(mode))
		type[0] = '4';
	else if(S_ISDIR(mode))
		type[0] = '5';
	else if(S_ISFIFO(mode))
		type[0] = '6';
	else
		type[0] = '8';

	type[1] = '\0';
}

void get_username(char* username, uid_t user_id) {
	struct passwd * user_info = getpwuid(user_id);
	strcpy(username, user_info->pw_name);
}

void get_groupname(char* groupname, gid_t group_id) {
	struct group * group_info = getgrgid(group_id);
	strcpy(groupname, group_info->gr_name);
}

void get_device_numbers(char* devmajor, char* devminor, dev_t devnumber) {
	char buff[8];
	
	sprintf(buff, "%lu", MAJOR(devnumber));
	sprintf(devmajor, "%lld", dec2oct(buff));

	sprintf(buff, "%lu", MINOR(devnumber));
	sprintf(devminor, "%lld", dec2oct(buff));
}

void fulfill_empty_space(char* string, int starting_point, int length) {
	int i;
	
	for(i = starting_point; i < length; i++)
		string[i] = '\0';
}

void calculate_checksum(FILE_HEADER* header) {
	int i = 0;
	int j = 0;
	int sum = 0;
	int offset = 0;
	char buffer[8];

	while(j < HEADER_S) {
		if(j < NAME_S) {
			offset = NAME_S;
			while(j < offset) {
				sum += (int) header->name[i++];
				j++;
			}
		}
		else if(j < offset + MODE_S) {
			offset += MODE_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->mode[i++];
				j++;
			}
		}
		else if(j < offset + UID_S) {
			offset += UID_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->uid[i++];
				j++;
			}
		}
		else if(j < offset + GID_S) {
			offset += GID_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->gid[i++];
				j++;
			}
		}
		else if(j < offset + SIZE_S) {
			offset += SIZE_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->size[i++];
				j++;
			}
		}
		else if(j < offset + MTIME_S) {
			offset += MTIME_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->mtime[i++];
				j++;
			}
		}
		else if(j < offset + CKSUM_S) {
			offset += CKSUM_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->cksum[i++];
				j++;
			}
		}
		else if(j < offset + TYPEFLAG_S) {
			offset += TYPEFLAG_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->typeflag[i++];
				j++;
			}
		}
		else if(j < offset + LINKNAME_S) {
			offset += LINKNAME_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->linkname[i++];
				j++;
			}
		}
		else if(j < offset + MAGIC_S) {
			offset += MAGIC_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->magic[i++];
				j++;
			}
		}
		else if(j < offset + VERSION_S) {
			offset += VERSION_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->version[i++];
				j++;
			}
		}
		else if(j < offset + UNAME_S) {
			offset += UNAME_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->uname[i++];
				j++;
			}
		}
		else if(j < offset + GNAME_S) {
			offset += GNAME_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->gname[i++];
				j++;
			}
		}
		else if(j < offset + DEVMAJOR_S) {
			offset += DEVMAJOR_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->devmajor[i++];
				j++;
			}
		}
		else if(j < offset + DEVMINOR_S) {
			offset += DEVMINOR_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->devminor[i++];
				j++;
			}
		}
		else if(j < offset + PREFIX_S) {
			offset += PREFIX_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->prefix[i++];
				j++;
			}
		}
		else if(j < offset + STUFFING_S) {
			offset += STUFFING_S;
			i = 0;
			while(j < offset) {
				sum += (int) header->stuffing[i++];
				j++;
			}
		}
	}

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