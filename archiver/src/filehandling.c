#include "../head/filehandling.h"
#include "../head/utilitarian.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

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
		path[0] = '\0';
	}
	else if(last_separator_position == -1) {
		// This is when it's just a file (everything except a directory)
		strcpy(filename, full_path);
		path[0] = '\0';
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
		path[last_separator_position + 1] = '\0';
		filename[j + 1] = '\0';
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
	char buff[5] = {0};
	sprintf(buff, "%d", id);
	id = dec2oct(buff);

	// UID / GID range is between 0 and 32767 so 2 first positions are always 
	// at 0.
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
	sprintf(filesize, "%ld", size);
	sprintf(filesize, "%d", dec2oct(filesize));
}