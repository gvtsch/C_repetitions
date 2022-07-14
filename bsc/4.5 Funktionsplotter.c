/***********************************************
# main.c 
# 4.5 Funktionsplotter
# 
# Christoph Kempkes HS OS
# Erstellung: 11. Oktober 2012
# Testiert: 18. Oktober 2012
#
# ToDo:
#
************************************************/

#include <stdio.h>			// Bibliotheken laden
#include <stdlib.h>
#include <math.h>

int main(){

	double a;				// a = untere Grenze
	double b;				// b = untere Grenze
	double x;				// x = Werteabstand
	int n;

	double s;				// Sinus
	double c;				// Cosinus
	double l;				// Logarithmus 

	int i;

	printf("Untere Grenze des Wertebereiches eingeben:\n");		// Untere Grenze einlesen und
	scanf("%lf",&a);											// auf a schreiben
	printf("Obere Grenze des Wertebereiches eingeben:\n");		// Obere Grenze einlesen und
	scanf("%lf",&b);											// auf b schreiben
	printf("Zeilenzahl n eingeben:\n");
	scanf("%d", &n);
	
	x = (b-a)/(n-1);

	printf("Der Werteabstand betraegt: %fl\n", x);
	printf("x		 sin(x)		 cos(x)		 log(x)\n");				// Überschrift Tabelle

	for (i=1; i<=n; i++){			// For Schleife mit n Iterationen
		s = sin(a);					// Werte berechnen
		c = cos(a);
		l = log(a);
		
		if (a>0) {
			printf("%7.4lf		%7.4lf		%7.4lf		%7.4lf\n", a, s, c, l);		// Werte ausgeben
		}

		else {
			printf("%7.4lf		%7.4lf		%7.4lf		\tundef.\n", a, s, c);
		}
		
		a = a + x;					// Nächster Schritt
	}


	system("PAUSE");
	return 0;
}