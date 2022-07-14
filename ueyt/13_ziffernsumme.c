#include <stdio.h>
#include <stdlib.h>


int main () {

	int zahl, ziffernsumme;
	ziffernsumme = 0;

	printf("Zahl eingeben (max 999): ");
	scanf("%d", &zahl);

	ziffernsumme = zahl/100 + (zahl/10)%10 + zahl%10;

	printf("%d ... %d", zahl, ziffernsumme);
	

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}