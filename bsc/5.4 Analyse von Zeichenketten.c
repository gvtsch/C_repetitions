// main.c 
// 5.4 Analyse von Zeichenketten
//
// Christoph Kempkes HS OS
// Erstellung vom 28. Oktober 2012 bis 30. Oktober 2012
// Testiert am 01. Nov 2012
//
// ToDo: Schreiben Sie eine Funktion count(), die als Eingabeparameter (call-by-value) eine Zeichenkette string enthält, 
// die zuvor über die Tastatur eingelesen worden ist. In der o.g. Funktion sind die Anzahl der Vokale vok, die Anzahl der 
// Konsonanten kon und die Anzahl von Sonderzeichen son (Zeichen, die weder Vokal noch Konsonant sind) zu bestimmen. 
// Die Funktion count() soll als Rückgabewert die Anzahl aller Zeichen von string zurückliefern. Des Weiteren sind die 
// Werte vok, kon, son an die aufru-fende Funktion zurückzugeben. Dieses hat über Zeiger zu erfolgen (call-by-reference).
// In der Funktion main() hat die Eingabe, der Aufruf von count() und die Ausgabe der Werte 
// (Gesamt-zahl, Vokale, Konsonanten, Sonderzeichen) zu erfolgen. Die Eingabe kann Groß- und Kleinbuchstaben enthalten!
// Die Aufgabe ist ohne Benutzung von Bibliotheksfunktionen außer zur Ein- und Ausgabe zu lösen.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Input
void input(char *text){
	
	printf("Geben Sie den Text ein (Max 255 Zeichen): \n");
	scanf("%[^\n]", text);		// Inklusive Leerzeichen scannen
}


// Count
void count(char *text, int *vok, int *kon, int *son, int *ges, char *vokale, char *konsonanten){
	
	int i, k = 0;
	*kon = 0;
	*vok = 0;
	*son = 0; 
	*ges = 0;
	
	// Gesamtzahl
	for (i=0; text[i] != '\0'; i++) {
		(*ges)++;
	}

	// Konsonanten
	for (i = 0; i <= 42; i++){					// Solange 'Anzahl der Konsonanten sowohl 'Groß' als auch 'klein''
		for (k = 0; k <= *ges; k++){			// Solange k kleiner als Gesamtlaenge
			if (konsonanten[i] == text[k]){		// Pruefen, ob Konsonant
				(*kon)++;}						// Falls ja: kon + 1
		}
	}

	// Vokale
	for (i = 0; i <= 9; i++){					// Solange 'Anzahl der Vokale sowohl 'Groß' als auch 'klein''
		for (k = 0; k <= *ges; k++){			// Solange k kleiner als Gesamtlaenge
			if (vokale[i] == text[k]){			// Pruefen, ob Vokal
				(*vok)++;}						// Falls ja: vok + 1
		}
	}

	// Sonderzeichen
	*son = *ges - (*vok + *kon);				// Gesamtlaenge - Vokale - Konsonaten
}


// Output
void output(char *text, int vok, int kon, int son, int ges){
	
	printf("\n\nGesamtzahl:	%d\n", ges);
	printf("Konsonanten:	%d\n", kon);
	printf("Vokale:		%d\n", vok);
	printf("Sonderzeichen:	%d\n", son);
}


// Main
int main() {

	int vok, kon, son, ges = 0;		// Vokale, Konsonanten, Sonderzeichen, Gesamt
	char text[255] = {0};			// char text mit 255 Zeichen
	char vokale[10] = {'a', 'e', 'i', 'u', 'o', 'A', 'E', 'I', 'O', 'U'};		// Vokale 'groß' und 'klein'
	char konsonanten[42] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',	// char konsonanten mit Vokale 'klein'
						    'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z'};	// und Vokale 'groß'

	printf("5.4 Analyse von Zeichenketten\n\n\n");
	
	
	input(text);	// Input aufrufen
	count(text, &vok, &kon, &son, &ges, vokale, konsonanten);		// count aufrufen
	output(text, vok, kon, son, ges);		// output aufrufen
	

	printf("\n\n\n");	// nur ein paar Leerzeilen
	system("PAUSE");	// Kommandozeile anhalten
	return 0;
}