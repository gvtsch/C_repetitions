#include <stdio.h>
#include <stdlib.h>


void giveback(int *w, int i){
	i = 100;
	*w = 1000;
}

int main () {

	int w = 0;
	int i = 3;

	giveback(&w, i);
	printf("i...%d\nw...%d", i, w);

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}