// main.c 
// 5.5 Skalarprodukt
//
// Christoph Kempkes HS OS
// Erstellung am 24. Oktober 2012
// Testiert am
// ToDo:


//Einladen der Bibliotheken
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Input
void input(float* vektor_a,float* vektor_b,int* anzahl) {		// * um die Speicheradresse übergeben zu können
	
	int i=0;	// i für For-Schleife

	printf("Anzahl der Vektorkoordinaten eingeben: ");	// Anzahl der Vektorkoordinaten eingeben
	 scanf("%d", anzahl);								// und einlesen

	 //Eingabe
	for(i=0;i<*anzahl;i++) {		// Solange i < Anzahl der Vektorkoordinaten
		printf("\n%d. Koordinate des Vektors A eingeben: ", i+1);		// Aufforderung zur Eingabe des "i+1"ten Wert
		scanf("%f", &(vektor_a[i]));	// und einlesen
		printf("%d. Koordinate des Vektors B eingeben: ", i+1);			// Wie bei A
		scanf("%f", &(vektor_b[i]));	// und einlesen
	}
}

// Product
void product(float* vektor_a, float* vektor_b, float* ergebnis, int anzahl) {	// Vektoren und Ergebnis zum weitergeben; Anzahl nicht
	
	int i=0;	// i für For-Schleife
	float erg=0.0;		// Ergebnis als Fließkommazahl und 0 deklinieren

	for(i=0; i<anzahl; i++) {		// Solange i < Anzahl der Vektorkoordinaten
		(*ergebnis) += ((vektor_a[i])*(vektor_b[i]));		// Ergebnis = Ergebnis + (VektorA*VektorB)
	}
}

// Output
void output(float ergebnis) {		// Ergebnis braucht nicht weiter gegeben werden, da es nur ausgegeben wird

	printf("\nDas Skalarprodukt ist %f\n\n", ergebnis);		// Ausgabe
}


// Main
int main()
{
    //Deklaration der Variablen
	int anzahl=0;		// Anzahl der Vektorkoordinaten
	float vektor_a[10], vektor_b[10], ergebnis=0.0;		// Als Fliesskommazahl: VektorA + B max 10 Zeichen; Ergebnis

    printf("Aufgabe 5.5 - Skalarprodukt\n\n");
    
	input(vektor_a, vektor_b, &anzahl);		// Bereitstellen der Vektoren und Anzahl der Vektorkoordinaten
	product(vektor_a, vektor_b, &ergebnis, anzahl);		// Bereitstellen der Vektoren, der Anzahl der Vektorkoordinaten und des Ergebnisses
	output(ergebnis);	// Ergebnis

	system("PAUSE");	// Kommandozeile anhalten
	return 0;
}