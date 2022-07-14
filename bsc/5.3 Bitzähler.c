/*main.c 
5.3 Bitzähler

Christoph Kempkes HS OS
Erstellung vom 28. Oktober 2012 bis 15.November 2012
Testiert am */

// Laden der Bibliotheken
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*void dual(unsigned int ergebnis){
	if((ergebnis) != 0) {
		dual(ergebnis/2);
	}
	if(((ergebnis)%2) == 0) {
		printf("0");
	}
	else {
		printf("1");
	}
}*/


// Main
int main (){

	unsigned int zahl1, zahl2;		
	unsigned int length, one, i, change, bit, artof, ergebnis = 0;
	int dual[32]={0};
	
		/* Variablenzuweisung
			zahl1, zahl2	= zu bearbeitende Zahl(en)
			length			= Laenge der Variable in Bit
			one				= Zaehlvariable fuer Einsen im Bitmuster
			i				= Zaehlvaribale fuer Schleife
			change			= Verknuepfungsvariable zum Aendern des Bitmuster
			bit				= Zu aenderndes Bit
			artof			= Art der Aenderung:	1 -> ausgewaehltes Bit -> 1
													0 -> ausgewaehltes Bit -> 0
			ergebnis		= Ergebnisablage Bitveraenderung 
			dual			= Wird fuer Dualzahlen benoetigt
			*/
		
	printf("5.3 Bitzaehler\n\n");
		
	length = sizeof(zahl1) * 8;		// Laenge wird berechnet
	printf("Laenge der Binaerzahl darf %d-Bits haben.\n", length);

	artof, one = 0;		

	printf("Bitte eine Zahl eingeben: ");
	scanf("%d", &zahl1);	// zahl1 einscannen
	zahl2 = zahl1;			// zahl1 an zahl2 übergeben
		
		// Einsen zählen
		for(i = 0; i < length; i++){
			if(zahl1 & 1){				// Wenn letztes Bit 1, dann ...
				one++;					// ... Zaehler um 1 erhoehen ...
				zahl1 = zahl1 >> 1;		// ... und Bitmuster um 1 nach rechts verschieben (quasi halbieren) und in zahl1 abelgen
			}
			else {						// ... sonst ...
				zahl1 = zahl1 >> 1;		// ... nur Bitmuster verschieben
			}
		}

		printf("Die Anzahl der Einsen im Bitmuster: %d\n", one);	
		printf("Welches Bit soll veraendert werden? Bit von 1 - %d von rechts gezaehlt: ", length);
		scanf("%d", &bit);
		printf("Wert fuer das zu veraendernde Bit eingeben (0 oder 1): ");
		scanf("%d", &artof);

		// "Umrechnen"
		if( (bit > length) || (bit < 1) || (artof < 0) || (artof > 1)){		// Eingabeüberprüfung
			printf("Ungueltige Eingabe...\a\n");
			
			printf("\n\n\n");		// Nur ein paar Leerzeilen
			system("PAUSE");		// Anhalten der Kommandozeile
			return 0;	
		
		} else if (artof == 1){					// ... Bit soll auf 1 geändert werden
				change = 1 << (bit - 1);		// Change wird die "veraenderte" Zahl	// Eine 1 wird an das gewuenschte Bit geschoben
				ergebnis = zahl2 | change;		// Vergleich zwischen der ursprünglichen und veränderten Zahl durch ODER
				printf("Die veraenderte Zahl lautet: %u\n", ergebnis);
			}
			else {								// ... Bit soll auf 0 geändert werden
				change = 1 << (bit - 1);		// Change wird die "veraenderte" Zahl	// Eine 1 wird an das gewuenschte Bit geschoben
				ergebnis = zahl2 & ~change;		// Vergleich zwischen der ursprünglichen und veränderten Zahl durch UND
				printf("Die veraenderte Zahl lautet: %u\n", ergebnis);
			}

			// Dualzahl berechnen
			// dual(ergebnis);

			i = 31;
			printf("Bitmuster: ");
			for(ergebnis; ergebnis != 0; ergebnis=ergebnis/2){
				//printf("%d", (ergebnis%2));
				
				if((ergebnis%2) == 0){
					dual[i] = 0;
					i--;
				} else {
					dual[i] = 1;
					i--;}
				} 
			for (i = 0; i <= 31; i++) {		printf("%d", dual[i]);		}
				
	printf("\n\n\n");		// Nur ein paar Leerzeilen
	system("PAUSE");		// Anhalten der Kommandozeile
	return 0;
}
