// main.c 
// 6.2 Zufallszahlen
//
// Christoph Kempkes HS OS
// Erstellung vom 16.11.2012
// Testiert am

// Bibliotheken laden
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

// Zufallszahlen generieren
void zufallszahlen(double *zahlen, double *s, double *m, int *n){
	
	double d1 = 0, d2 = 0, x = 0;
	int i = 0;
	srand(time(NULL));
	
	printf("\n\na... Generieren von n gauss-verteilten Zufallszahlen.\nn (max. 1000), m und s sind einzugeben.\n");
	printf("n... "); scanf("%d", &*n); // zahlen[(*n)];
	printf("m... "); scanf("%lf", &*m);
	printf("s... "); scanf("%lf", &*s);

	for (i = 0; i < (*n); i++){
		
		zahlen[i] = 0.0;
		d1 = ( (double) rand() ) / RAND_MAX;		// d1 ... Gegebene Formel
		d2 = ( (double) rand() ) / RAND_MAX;		// d2 ... Gegebene Formel
        
		// Zufallszahlen berechnen
        x = ( (*m) + (*s) * (sqrt(-2.0 * log(d1)) * cos(2.0 * M_PI * (d2))));
		zahlen[i] = x;
	}
	//zahlen[i+1]='\0';
	printf("\n----------\n");
	printf("\n\n\n");		// Nur ein paar Leerzeilen
}

// Zahlen Ausgabe
void ausgabe(double *zahlen, int *n){
	int i = 0;

	printf("b... Ausgabe der Zufallszahlen.\n");
	for(i = 0; i < (*n); i++)		printf("%d... %lf\n", i + 1, zahlen[i]);

	printf("\n----------\n");
	printf("\n\n\n");		// Nur ein paar Leerzeilen
}

// Häufigkeiten berechnen
void sortieren(double *zahlen, int *intervall, double *m, double *s, int *n){
	int i = 0;
	double relativ = 0.0;
	
	printf("c... Einordnen in die Haeufigkeitsintervalle.\n");
	for(i = 0; i < 8; i++){		intervall[i] = 0;}
	
	i=0;
	// Zaehlen
	
		for(i = 0; i < (*n); i++){
		
			if (zahlen[i]  < ((*m) - 3 * (*s)))												{	intervall[0]++;	}
			if ((zahlen[i] >= ((*m) - 3 * (*s))) && (zahlen[i] < ((*m) - 2 * (*s))))		{	intervall[1]++;	}
			if ((zahlen[i] >= ((*m) - 2 * (*s))) && (zahlen[i] < ((*m) - (*s))))			{	intervall[2]++;	}
			if ((zahlen[i] >= ((*m) - (*s)))	 && (zahlen[i] < (*m)))						{	intervall[3]++;	}
			if ((zahlen[i] >= (*m))				 && (zahlen[i] < ((*m) + (*s))))			{	intervall[4]++;	}
			if ((zahlen[i] >= ((*m) + (*s)))	 && (zahlen[i] < ((*m) + 2 * (*s))))		{	intervall[5]++;	}
			if ((zahlen[i] >= ((*m) + 2 * (*s))) && (zahlen[i] < ((*m) + 3 * (*s))))		{	intervall[6]++;	}
			if (zahlen[i]  >= ((*m) + 3 * (*s)))											{	intervall[7]++;	}
		}
	


	// Ausgabe
	for(i = 0; i < 8; i++){
		relativ = (double)intervall[i] * 100 / (*n);
		printf("Intervall %d ... %d ... %.02lf%%\n", i, intervall[i], relativ);
	}
	printf("\n%d\n", intervall[0]+intervall[1]+intervall[2]+intervall[3]+intervall[4]+intervall[5]+intervall[6]+intervall[7]);
	printf("\n----------\n");
	printf("\n\n\n");		// Nur ein paar Leerzeilen
}

// Swap
void swap(double *zahlen, int i, int j){
	double dreieck = 0.0;

	// Zahlen[i] in "Zwischenspeicher" (Dreieckstausch)
	dreieck = zahlen[i];
	zahlen[i] = zahlen[j];
	zahlen[j] = dreieck;

}

// Simplesort
void simplesort(double *zahlen, int *n){
	int i, j, p = 0;

	/* Schleife über Position = 1 .. N
	{	Schleife über Postion' = Position + 1 .. N
	{	Falls x[Position] > x[Position'] ...
	{	... dann Vertausche x[Position] und x[Position'] }}}
	*/

	printf("d... Sortieren der Zufallszahlen.\n");

	for(i = 0; i < (*n); i++){
		for(j = i + 1; j < (*n); j++){
			if(zahlen[i] > zahlen[j]){
				swap(zahlen, i, j);}
		}
	}

	printf("\nSollen die sortierten Zahlen ausgegeben werden?\n1... ja\n2...nein\n"); scanf("%d", &p);
	if(p != 1 && p != 2){
		printf("Ungueltige Eingabe. Wiederholen!\n1... ja\n2...nein\n"); scanf("%d", &p);
	} else 	if(p == 1) {
		for(i = 0; i < (*n); i++)	{ printf("%d...%lf\n", i + 1, zahlen[i]); }
	}

	printf("\n----------\n");
	printf("\n\n\n");		// Nur ein paar Leerzeilen
}

// Main
int main(){

	char wahl;
	double m, s = 0.0;
	double zahlen[1000]={0.0};
	int intervall[8]={0.0};
    int n = 0;


	printf("6.1 Zufallszahlen\n\n\n");

	while(1) {
	printf("Waehlen zwischen:\n");
	printf("a... Generieren von n gauss-verteilen Zufallszahlen.\nn (max. 1000), m und s sind einzugeben\n");
	printf("b... Ausgabe der Zufallszahlen am Bildschirm\n");
	printf("c... Ausgabe der Haeufigkeiten\n");
	printf("d... Sortieren der Zufallszahlen\n");
	printf("e... Ende\n");
	
	printf("\nIhre Wahl: ");
	scanf("%c", &wahl);
	
	if (wahl == 'a' || wahl == 'A'){
		zufallszahlen(zahlen, &s, &m, &n);}
	if (wahl == 'b' || wahl == 'B'){
		ausgabe(zahlen, &n);}
	if (wahl == 'c' || wahl == 'C'){
		sortieren(zahlen, intervall, &m, &s, &n);}
	if (wahl == 'd' || wahl == 'D'){
		simplesort(zahlen, &n);}
	if (wahl == 'e' || wahl == 'E'){break;};
	wahl = getchar();
	} 

	printf("\n\n\n");		// Nur ein paar Leerzeilen
	system("PAUSE");		// Kommandozeile anhalten
	return 0;
}
