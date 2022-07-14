/***********************************************
# main.c 
# 4.2 Zufallszahl
# 
# Christoph Kempkes HS OS
# Erstellung: 13. Oktober 2012
# Testiert: 18. Oktober 2012
#
# ToDo:
#
************************************************/

#include <stdio.h>														// Bibliotheken einlesen
#include <stdlib.h>
 
int main() {		
        int zahl = 0;													// Variablen definieren
        int i = 0;
        int s = 0;
 
       
        printf("Geben sie den Startwert ein.\n");						// Aufforderung zum Startwert eingeben
        scanf("%d", &s);												// Startwert einlesen
        srand(s);														// Startwert in den Algorithmus mit einbeziehen
       
        printf("\n\nZufallszahlen:\n");									// Ausgabe
 
 
        for (i = 1; i <= 6; i++) {										// For Schleife. Start i=1. Jeden Durchlauf wird i=i+1 bis i<=6
                zahl = (rand());										// Zahl generieren
                printf("%d\n", zahl);									// Ausgabe
        }
 
        system("PAUSE");												// Kommandozeile anhalten
        return 0;
}