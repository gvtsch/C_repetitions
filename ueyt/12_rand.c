#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
	
	int zufall;

	srand(time(NULL));
	zufall = rand()%100 + 1;

	printf("Zahl = %d", zufall);
	
	printf("\n\n\n");
	system("PAUSE");
	return 0;
}