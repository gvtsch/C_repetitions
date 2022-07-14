#include <stdio.h>
#include <stdlib.h>

int main () {
	int zahl1, zahl2;

	printf("zahl1: ");
	scanf("%d", &zahl1);
	printf("zahl2: ");
	scanf("%d", &zahl2);

	if (zahl1 == zahl2) {
		printf("Die Zahlen sind gleich.\n");
	}
	else {
		printf("Die Zahlen sind nicht gleich.\n");
	}
	

	system("PAUSE");
	return 0;
}