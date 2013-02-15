#include "../head/utilitarian.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

int oct2dec(char* c) {
	unsigned int i = 0;
	int n = strlen(c) - 1;
	int result = 0;

	// When browsing a char* table in C, getting the ith cell correspond to get
	// all cells from i to the end. It's necessary to divide by power of 10.
	// Cast to int the division is as well needed in order to avoid a 
	// multiplication by a float.
	for(i = 0; i < strlen(c); i++) {
		result += ( ((int)(atoi(&c[i]) / pow(10, n))) * pow(8, n));
		n--;
	}

	return result;
}

int dec2oct(char* c) {
	int octal[12] = {0};
	int i = 0;
	int result = atoi(c);

	while(result != 0) {
		octal[i] = result % 8;
		result /= 8;
		i++;
	}

	result = 0;
	i--;

	while(i != -1) {
		result += (octal[i] * pow(10, i));
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