/***********************************************
# verzinsung_4_2.c 
# 4.2 Verzinsung
# 
# Christoph Kempkes HS OS
# Erstellung: 09. Oktober 2012
# Testiert: 11.10.2012
#
# ToDo:
#
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ()
{
	
	double k,p=0;													// k (Kapital) und p (Zinssatz) als Gleitkommazahlen definieren und auf 0 setzen
	int l=0;														// l (Laufzeit) als ganze Zahl deklarieren und auf 0 setzen

	printf("Kapital eingeben:\n");									// Einlesen des Kapitals
	scanf("%lf", &k);
	printf("Laufzeit eingeben:\n");									// Einlesen der Laufzeit
	scanf("%d", &l);
	printf("Prozentsatz eingeben:\n");								// Einlesen des Prozentsatzes
	scanf("%lf", &p);
    
	k=k*(pow((1+(p/100)),l));										// K(n,p)= K*(1+p/100)^l 

    printf("Das neue Kapital betraegt %.2f EUR.\n",k);				// Ausgabe des neuen Kapitals
	system("PAUSE");												// Kommandozeile bleibt geöffnet
	return 0;
}