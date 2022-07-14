#include <stdio.h>
#include <stdlib.h>

int main () {

	int a, ok;
	char dummy;

	printf("Geben sie eine Zahl ein: ");
	ok = scanf("%d%c", &a, &dummy);

	if (ok == 2 && dummy == '\n'){
		printf("Die Eingabe war korrekt\n");
	} else {
		printf("Falsche Eingabe\n");
	}

	system("PAUSE");
	return 0;
}