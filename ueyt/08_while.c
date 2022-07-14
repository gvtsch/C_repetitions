#include <stdio.h>
#include <stdlib.h>

int main () {

	char auswahl;
	int ende = 0;

	while (!ende) {

		printf("Waehlen Sie zwischen a, b, c und e.\n");
		printf("Ihre Wahl: ");
		scanf("%c", &auswahl);

		switch (auswahl) {

		case 'a':
			printf("Sie haben a gewaehlt\n");
			break;
		case 'b':
			printf("Sie haben b gewaehlt\n");
			break;
		case 'c':
			printf("Sie haben c gewaehlt\n");
			break;
		case 'e':
			printf("Das Programm wird beendet\n");
			ende = 1;
			break;
		}
	}


	system("PAUSE");
	return 0;
}