// main.c
// 7.2 Conway's Game Of Life
//
// Christoph Kempkes HS OS
// Erstellung vom 21.11.2012 bis 26.11.2012
// Testiert am,

// Bibliotheken laden
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
 

// Update
void update_array (int a[MAX][MAX],int *zeilen, int *spalten){
	
	int b[MAX][MAX] = {0};			
	int i, j, n;					

	// Hilfsvariable b werden Werte aus a zugewiesen
	// um die diese dann zu verarbeiten
	for(i = 0; i < (*zeilen); i++) {
		for(j = 0; j < (*spalten); j++) {
			b[i][j] = a[i][j];
		}
	}

	// Angrenzende lebende Zellen zaehlen
	// Da es nur 8 angrenzende Zellen gibt, gibt es nur 8 Bedingungen (inkl. Prüfung, ob noch innerhalb der Matrix)
	for(i = 0; i < (*zeilen); i++) {
		for(j = 0; j < (*spalten); j++) {
			n = 0;

			if(b[i-1][j-1] == 1 && i > 0			&& j > 0			) n++;	// links oben
			if(b[i  ][j-1] == 1						&& j > 0			) n++;	// links
			if(b[i+1][j-1] == 1 && i <= (*zeilen)	&& j > 0			) n++;	// links unten
			if(b[i-1][j  ] == 1 && i > 0								) n++;	// oben
			if(b[i+1][j  ] == 1 && i <= (*zeilen)						) n++;	// unten
			if(b[i-1][j+1] == 1 && i > 0			&& j <= (*spalten)  ) n++;	// rechts oben
			if(b[i  ][j+1] == 1						&& j <= (*spalten)  ) n++;	// rechts
			if(b[i+1][j+1] == 1 && i <= (*spalten)	&& j <= (*spalten)	) n++;	// rechts unten

			// Unterbevölkert / Überbevölkert -> Sterben
			if(n < 2 || n > 3) a[i][j] = 0;	

			// Weder ... noch ... -> Neues Leben
			if(n == 3) a[i][j] = 1;	
			
		}
	}
}

// Ausgabe
void display_array(int a[MAX][MAX], int *zeilen, int *spalten) { 
    
	int i, j = 0;
	
	// Ausgabe der aktuellen Matrix
	for(i = 0; i < (*zeilen); i++) { 
        for(j = 0; j < (*spalten); j++) { 
            printf(" %d", a[i][j]); 
        } printf("\n"); 
    } printf("\n"); 
} 

// Main
int main(int argc, char **argv) {
	    
	int i, j, schritte, zeilen, spalten;
	int runde = 1;
	char name[MAX], datein[20];
	int a[MAX][MAX] = {0};
	
	const char LIFEOUT[] = "lifeout.txt";
	FILE *ein = fopen (argv[3], "r");
	FILE *aus = fopen (LIFEOUT, "w");
	
	
	printf("7.2 Conway's Game Of Life\n\n");
	
	// Genug Parameter eingegeben?
	if(argc < 5) {
		printf("Nicht genuegend Parameter.\n");
		printf("\n\n\n");
		system("PAUSE");
		return EXIT_FAILURE;
	}

	// Parameter auslesen
	sscanf(argv[1], "%d", &zeilen);		// Zeilen
	sscanf(argv[2], "%d", &spalten);	// Spalten
	sscanf(argv[4], "%d", &schritte);	// Iterationen
	// Zur Überprüfung nochmals ausgeben
	printf("Dateiname... %s\n", argv[3]); printf("Zeilen... %d\n", zeilen); printf("Spalten... %d\n", spalten); printf("Schritte... %d\n", schritte);
		
	// Eingabeüberprüfungen
	if ((ein == NULL) || (aus == NULL)) {				// Können Dateien geöffnet werden?
		printf("Fehler beim Oeffnen der Datei\n");		// Nein? Fehler.
		fclose(ein); fclose(aus);						// Dateien schließen
		return EXIT_FAILURE;							// Fehler zurückgeben
	} else {										// Ja?
		while(fgets(name, MAX, ein)){				// Datei auslesen
			if (name[0] == '#') continue;			// # zu Beginn der Zeile?

			if (sscanf(name,"%d %d", &i, &j) == 2) {				// 2 Zahlen in der Zeile?
				if (i >= 0 && i <= zeilen && j >= 0 && j <= spalten){		// Innerhalb des Zahlenbereichs?
				printf("%d %d\n", i, j);							// Inhalt der Datei (ohne #-Zeilen) am Bildschirm ausgeben
				fprintf(aus, "%d %d\n", i, j);						// Inhalt der Datei (ohne #-Zeilen) in 2. Datei schreiben
				a[i][j] = 1;										// Koordinate auf 1 (lebendig) setzen
				} else printf("Zahlen nicht im Zahlenbereich!\n");
			} else {
			printf("Fehler!\n");		// Keine 2 Zahlen in der Zeile
			system("PAUSE");			// Kommandozeile anhalten
			return EXIT_FAILURE;		// Fehler zurückgeben
			}
		}
	}

	// Originalmatrix ausgeben
	printf("\n\nDie eingegebene Matrix:\n\n");
	display_array(a, &zeilen, &spalten);
	
	// Ausführen / Berechnen und Ausgeben
	for(i = 0; i < schritte; i++) {				
		update_array(a, &zeilen, &spalten);		
		printf("\n\nRunde %d\n", i + 1);		
		display_array(a, &zeilen, &spalten);	
		//for(j = 0; j < i; j++) system("cls");
	}
	
	// Letzte Runde in Datei ausgeben
	fprintf(aus, "\n\nRunde %d\n", schritte);
	for(i = 0; i < zeilen; i++) { 
        for(j = 0; j < spalten; j++) { 
            fprintf(aus, " %d", a[i][j]); 
        } fprintf(aus, "\n"); 
    } fprintf(aus, "\n"); 

	// Dateien schließen
    fclose(ein); fclose(aus);
    
    printf("\n\n\n");
    system("PAUSE");
    return EXIT_FAILURE;
}
