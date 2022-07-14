#include <stdio.h>
#include <stdlib.h>

int main () {

	int auswahl;

	printf("Waehlen Sie zwischen 1, 2 und 3.\n");
	printf("Ihre Wahl: ");
	scanf("%d", &auswahl);

	switch (auswahl) {

	case 1:
		printf("Sie haben 1 gewaehlt\n");
		break;
	case 2:
		printf("Sie haben 2 gewaehlt\n");
		break;
	case 3:
		printf("Sie haben 3 gewaehlt\n");
		break;
	}

	system("PAUSE");
	return 0;
}