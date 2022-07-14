#include <stdio.h>
#include <stdlib.h>

int main () {

	int zahl;

	printf("Geben sie eine Zahl ein (<=10000): ");
	scanf("%d", &zahl);

	for(zahl; zahl <= 10000; zahl++){

		printf("Zahl = %d\n", zahl);
	}

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}