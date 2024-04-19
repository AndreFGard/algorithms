#include <stdio.h>
int printarray(char array[], int size, int n, char format[]) {
	for (int i=0;i<n;i++) {
		printf(format, array[i*size]);
	}
	puts("");
	return 0;
}