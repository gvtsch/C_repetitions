#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {

	double weg=0;
	double speed=0;
	double zeit=0;
	int wahl=0;

	printf("1...Weg\n");
	printf("2...Geschwindikeit\n");
	printf("3...Zeit\n");
	printf("\nIhre Wahl: ");
	scanf("%d", &wahl);

	if (wahl == 1 || wahl == 2 || wahl == 3) {
		switch (wahl) {
		case 1:
			printf("Sie moechten den Weg berechnen.\n");
			printf("Geben sie die Geschwindigkeit ein (km/h): ");
			scanf("%lf", &speed);
			printf("Geben Sie die Zeit ein (Minuten): ");
			scanf("%lf", &zeit);
			if (zeit != 0){
				weg = speed * (zeit/60);
				printf("In %.2lf Minuten bei %.2lf km/h wurde eine Strecke von %.2lf km zurueckgelegt.\n", zeit, speed, weg);
			}
			break;
		case 2:
			printf("Sie moechten die Geschwindigkeit berechnen.\n");
			printf("Geben sie die gefahrene Strecke ein (km): ");
			scanf("%lf", &weg);
			printf("Geben sie die Zeit ein (Minuten): ");
			scanf("%lf", &zeit);
			if (zeit != 0){
				speed = weg / (zeit/60);
				printf("Auf %.2lf km in %.2lf Minuten fuhren sie ein Durchschnittsgeschwindigkeit von %.2lf km/h\n", weg, zeit, speed);
			}
			break;
		case 3:
			printf("Sie moechten die Zeit berechnen.\n");
			printf("Geben sie die gefahrene Strecke ein (km): ");
			scanf("%lf", &weg);
			printf("Geben sie die Geschwindigkeit ein (km/h): ");
			scanf("%lf", &speed);
			if (speed != 0){
				zeit = weg / speed;
				printf("Fuer %.2lf km bei %.2lf km/h brauchten sie %.2lf Minuten Zeit\n\n\n", weg, speed, zeit * 60);
			}
			break;
		}
	} else {
		printf("Falsche Eingabe.\n\n\n");
	}



	system("PAUSE");
	return 0;
}