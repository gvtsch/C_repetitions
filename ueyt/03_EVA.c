#include <stdio.h>
#include <stdlib.h>

int main () {

	int zahl1, zahl2, ergebnis;
	printf("Geben sie die erste Zahl ein: ");
	scanf("%d", &zahl1);
	printf("Geben sie die zweite Zahl ein: ");
	scanf("%d", &zahl2);

	printf("----------------\n");
	printf("Das Ergebnis der Addition lautet: %d\n", zahl1 + zahl2);
	printf("Das Ergebnis der Multiplikation lautet: %d\n", zahl1 * zahl2);
	

	system("PAUSE");
	return 0;
}
