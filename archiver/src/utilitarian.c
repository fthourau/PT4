#include "../head/utilitarian.h"

#include <stdlib.h>
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

int files_end(char** files){
}
int files_begin(char** files){
	FILE* archive = fopen(files[2], "r");
	int taille = strlen(files[3]), trouve = 0, pos = 0, position = 0;
	FILE *f = fopen("debut", "w");
	char c;
	
	if(archive != NULL){
		archive = fopen(files[2], "r");
		while(fread(&c,1,1,archive)>0 && !trouve){
			if(c == files[3][pos-taille])
				pos++;
			else{
				fseek(archive,-pos,SEEK_CUR);
				pos=0;
			}

			trouve = (pos==taille);
			//subtraction of the size else this display the last 
			//character of the word and not the position of the word
			position = ftell(archive)-taille; 
			fprintf(f,"%c",c);
		}
		fclose(archive);
	}
		return position; //return the position of the word in the file
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

char* argument(int nb) {
	if(nb == 0)
		return "ne prend aucun argument";
	else
		return "prend un argument";
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

void printf_weight(unsigned long long int weight) {
	int unit = 0;
	int rest;
	char size[13];
	char n[2] = {'\0'};

	while(weight >= 1024) {
		rest = weight % 1024;
		weight /= 1024;
		unit++;
	}

	sprintf(size, "%lld", weight);
	strcat(size, ",");
	sprintf(n, "%d", rest / 100);
	strcat(size, n);

	if(unit == 1)
		strcat(size, "K");
	else if(unit == 2)
		strcat(size, "M");
	else if(unit == 3)
		strcat(size, "G");

	printf("%s", size);
}

void printf_date(unsigned long long int date) {
	struct tm* mtime;
	char date_str[32];

	static const char *jours[] = {
	    "Dimanche",
	    "Lundi",
	    "Mardi",
	    "Mercredi",
	    "Jeudi",
	    "Vendredi",
	    "Samedi"
    };

	mtime = localtime((time_t*)date);

	sprintf(date_str,
        "%s-%02d-%02d-%02d-%02d-%02d-%d",
        jours[mtime->tm_wday],
        mtime->tm_mday,
        mtime->tm_hour,
        mtime->tm_min,
        mtime->tm_sec,
        mtime->tm_mon + 1,
        mtime->tm_year + 1900);

	printf("%s", date_str);
}

void compress_with_gzip(char* filename) {
	char commandline[256] = { "gzip -c " };
	strcat(commandline, filename);
	strcat(commandline, " > ");
	strcat(commandline, filename);
	strcat(commandline, ".gz");
	system(commandline);
}