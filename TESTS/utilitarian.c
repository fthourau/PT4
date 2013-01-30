#include "utilitarian.h"
#include <math.h>
#include <string.h>

int oct2dec(char* c) {
	int i = 0;
	int n = strlen(c) - 1;
	int result = 0;

	for(i = 0; i < strlen(c); i++) {
		printf("i = %d | n = %d | r = %d\n", i, n, result);

		if( (i + 1) <= n)
			result += ( atoi(&c[i] - &c[i+1]) * pow(8, n));
		else
			result += ( atoi(&c[i]) * pow(8, n));

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