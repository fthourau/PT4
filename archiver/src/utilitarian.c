#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

unsigned long long int oct2dec(char* c) {
	int i;
	int n = 0;
	int length = strlen(c) - 1;
	unsigned long long int result = 0;

	for(i = length ; i >= 0 ; i--) {
		int l = ((int)c[i] % 48);
		result += (l * pow(8, n));
		n++;
	}

	return result;
}

unsigned long long int dec2oct(char* c) {
	unsigned long int div_result = atoi(c);
	int i = 0;
	unsigned long long int result = 0;
	unsigned long int octal[12] = {
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
		10000000000,
		100000000000,
	};

	while(div_result != 0) {
		octal[i] *= (div_result % 8);
		div_result /= 8;
		
		if(div_result != 0)
			i++;
	}

	while(i >= 0) {
		result += octal[i];
		i--;
	}

	return result;
}

int get_file_weight(FILE* file) {
	fseek(file, 0, SEEK_END);
	int t = ftell(file);
	rewind(file);

	return t;
}

bool is_tar_format(char* archive_to_check) {
	int len = strlen(archive_to_check);
	return ( (archive_to_check[len - 4] == '.') &&
			 (archive_to_check[len - 3] == 't') &&
			 (archive_to_check[len - 2] == 'a') &&
			 (archive_to_check[len - 1] == 'r') );
}

bool is_gzip_format(char* archive_to_check) {
	int len = strlen(archive_to_check);
	return ( (archive_to_check[len - 3] == '.') &&
			 (archive_to_check[len - 2] == 'g') &&
			 (archive_to_check[len - 1] == 'z') );
}

char* get_rights(char single_right_number) {
	switch(single_right_number) {
		case '7':
			return "rwx";
		case '6':
			return "rw-";
		case '5':
			return "r-x";
		case '4':
			return "r--";
		case '3':
			return "-wx";
		case '2':
			return "-w-";
		case '1':
			return "--x";
		case '0':
			return "---";
	}
	return "???";
}

char* get_weight(unsigned long long int weight) {
	unsigned long long int w = weight;
	int unit = 0;
	int rest;
	static char size[13];
	memset(size, 0, 13);

	while(w >= 1024) {
		rest = w % 1024;
		w /= 1024;
		unit++;
	}

	sprintf(size, "%lld", w);

	if(unit != 0) {
		char n[2] = {'\0'};
		strcat(size, ",");
		sprintf(n, "%d", rest / 100);
		strcat(size, n);
	}

	if(unit == 1)
		strcat(size, "K");
	else if(unit == 2)
		strcat(size, "M");
	else if(unit == 3)
		strcat(size, "G");
	else
		strcat(size, "o");

	return size;
}

char* get_asc_date(long int epoch_time) {
	struct tm* date = localtime(&epoch_time);

	return asctime(date);
}

void compress_with_gzip(char* filename) {
	char commandline[256] = { "gzip -c " };
	strcat(commandline, filename);
	strcat(commandline, " > ");
	strcat(commandline, filename);
	strcat(commandline, ".gz");
	system(commandline);
}

void decompress_with_gzip(char* filename) {
	char commandline[256] = { "gunzip " };
	strcat(commandline, filename);
	system(commandline);
}