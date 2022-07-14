// main.c 
// 5.5 Skalarprodukt
//
// Christoph Kempkes HS OS
// Erstellung am 23. Oktober 2012
// Testiert am
// ToDo:

// Laden der Bibliotheken
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Input
void input(float* a, float* b, int* n) {	// * um die Speicheradressen übergeben zu können

	printf("Bitte a eingeben: ");		// Eingaben anfordern
	scanf("%f", &*a);					// und einlesen
	printf("Bitte b eingeben: ");
	scanf("%f", &*b);
	printf("Bitte n eingeben: ");
	scanf("%d", &*n);
}

// Rekursion
float rekursion(float a, float b, int n) {	// Werte von a, b, n brauchen nicht weiter übergeben werden
 
	if(n==0) {		// Abfrage, ob n (Exponent) gleich 0 ist
		return 1.0;	
	}
	else {			// Wenn n ungleich 0 ist:
		return((a+b)*rekursion(a,b,n-1));	// Das Ergebnis der Rekursion wird zurückgegeben
	}
}

// Output
void output(float ergebnis) {	// Ergebnis braucht nicht übergeben werden

	printf("%f\n", ergebnis);	// Ergebnis wird ausgegeben
}

// Main
int main() {
    
	// Deklaration der Variablen
	int i=0, n=0;		// n = "Exponent"; i für For-Schleife
	float a,b,ergebnis=0.0;		// a, b, ergebnis als Fließkommazahlen

    printf("5.6 - Iteration und Rekursion\n\n");
    	
	// Input-Funktion aufrufen
	input(&a,&b,&n);		// Zur Eingabe von a, b, n
	
	// Iterative Berechnung
	ergebnis=1;		// Ergebnis auf 1 setzen, da für n = 0: (a+b)^0 = 1 
	
		for(i=0;i<n;i++){	// Solange i kleiner als Exponent
		ergebnis=ergebnis*(a+b);	// z.B. ergebnis = 1 * (a+b)
	}
	
	// Ausgabe der iterativen Berechnung
	printf("\nIterarische Berechnung: ");
	output(ergebnis);
	
	// Rekursive Berechnung
	ergebnis = rekursion(a,b,n);

	// Ausgabe
	printf("Rekursive Berechnung: ");
	output(ergebnis);
	printf("\n");

	system("PAUSE");		// Anhalten der Kommandozeile
	return 0;
}