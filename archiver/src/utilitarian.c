#include "../head/utilitarian.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

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