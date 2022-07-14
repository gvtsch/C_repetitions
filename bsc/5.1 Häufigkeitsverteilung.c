// main.c 
// 5.1 Haeufigkeitsverteilung
//
// Christoph Kempkes HS OS
// Erstellung vom 28. Oktober 2012 bis 30. Oktober 2012
// Testiert am
//
// ToDo: Zur Erzeugung Gauss-verteilter Zufallszahlen sind folgende Anweisungen notwenig:
// d1 = ((double)rand())/RAND_MAX;
// d2 = ((double)rand())/RAND_MAX;
// n = m + s*(sqrt(-2.0*log(d1))*cos(2.0*M_PI*d2));
//
// a) 1000 Zufallszahlen sollen am Bildschirm ausgegeben werden. m und s sind von der Tastatur ein-zulesen.
// b) In einem int-vektor mit 8 Elementen soll die H‰ufigkeit der in den Intervallen
// [-?,m-3s],[m-3s,m-2s],[m-2s,m-s],[m-s,m],[m,m+s],[m+s,m+2s],[m+2s,m+3s], [m+3s,?] 
// auftretenden Zufallszahlen gez‰hlt und anschlieﬂend absolut und prozentual am Bildschirm ausgege-ben werden.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES			
#include <math.h>
#include <time.h>


// Input 
void input (float *m, float *s){

	printf("Geben Sie m ein: ");
	scanf("%f", &*m);
	printf("Geben Sie s ein: ");
	scanf("%f", &*s);
}

// Count
void count (int *i, float *m, float *n, float *s, int *vektor, double *d1, double *d2, float *iv){
	
	srand(time(NULL));		// Fuer Zufallszahlen
	
	for (*i = 1; *i <= 1000; (*i)++){		// Solange i <= 1000 ...
		*d1 = ( (double) rand() ) / RAND_MAX;		// d1 ... Gegebene Formel
		*d2 = ( (double) rand() ) / RAND_MAX;		// d2 ... Gegebene Formel

		*n = (*m) + (*s) * (sqrt(-2.0 * log(*d1)) * cos(2.0 * M_PI * (*d2)));		// ... Gegebene Formel
		
		if ((*n) < ((*m) - 3 * (*s)))												// 1. Intervall
			vektor[0]++;			
		else if (((*n) >= ((*m) - 3 * (*s))) && ((*n) < ((*m) - 2 * (*s))))			// 2. Intervall
			vektor[1]++;
		else if (((*n) >= ((*m) - 2 * (*s))) && ((*n) < ((*m) - (*s))))				// 3. Intervall
			vektor[2]++;
		else if (((*n) >= ((*m) - (*s))) && ((*n) < (*m)))							// 4. Intervall
			vektor[3]++;
		else if (((*n) >= (*m)) && ((*n) < ((*m) + (*s))))							// 5. Intervall
			vektor[4]++;
		else if (((*n) >= ((*m) + (*s))) && ((*n) < ((*m) + 2 * (*s))))				// 6. Intervall
			vektor[5]++;
		else if (((*n) >= ((*m) + 2 * (*s))) && ((*n) < ((*m) + 3 * (*s))))			// 7. Intervall
			vektor[6]++;
		else if ((*n) >= ((*m) + 3 * (*s)))											// 8. Intervall
			vektor[7]++;
	
		printf("%d: %.2f\n", *i, *n);
	}

	for ((*i) = 0; (*i) < 8; (*i)++) {
		iv[*i]=(float)(vektor[*i]/10.0);
		
	} 
}

// Output
void output(int *vektor, float *iv, float *m, float *n, float *s){
	printf("Die Anzahl der Zahlen zwischen -unendlich und %.0f ist: %.2i\n",((*m) - 3 * (*s)), vektor[0]);
	printf("Das entspricht %.2f%%\n", iv[0]);
	printf("Die Anzahl der Zahlen zwischen %.0f und %.0f ist: %.2i\n",((*m) - 3 * (*s)), ((*m) - (2 * (*s))), vektor[1]);
	printf("Das entspricht %.2f%%\n", iv[1]);
	printf("Die Anzahl der Zahlen zwischen %.0f und %.0f ist: %.2i\n",((*m) - 2 * (*s)), ((*m) - (*s)), vektor[2]); 
	printf("Das entspricht %.2f%%\n", iv[2]);
	printf("Die Anzahl der Zahlen zwischen %.0f und %.0f ist: %.2i\n",((*m) - (*s)), (*m), vektor[3]);
	printf("Das entspricht %.2f%%\n", iv[3]);
	printf("Die Anzahl der Zahlen zwischen %.0f und %.0f ist: %.2i\n",(*m), ((*m) + (*s)), vektor[4]);
	printf("Das entspricht %.2f%%\n", iv[4]);
	printf("Die Anzahl der Zahlen zwischen %.0f und %.0f ist: %.2i\n",((*m) + (*s)), ((*m) + 2 * (*s)), vektor[5]);
	printf("Das entspricht %.2f%%\n", iv[5]);
	printf("Die Anzahl der Zahlen zwischen %.0f und %.0f ist: %.2i\n",((*m)+2*(*s)),((*m)+3*(*s)), vektor[6]);
	printf("Das entspricht %.2f%%\n", iv[6]);
	printf("Die Anzahl der Zahlen zwischen %.0f und unendlich ist: %.2i\n",((*m)+3*(*s)), vektor[7]);
	printf("Das entspricht %.2f%%\n", iv[7]);

	printf("%lf\n\n", iv[0]+iv[1]+iv[2]+iv[3]+iv[4]+iv[5]+iv[6]+iv[7]);
}


// Main
int main () {

	float n, m, s, in1, in2, in3, in4, in5, in6, in7, in8 = 0;		// d1, d2, n, m, s vorgegeben; in1 - in8 = Intervall 1 - Intervall 8
	int i;		// For Schleife
	double d1, d2 = 0;
	int vektor[8]={0};		// Array mit 8 Elementen f¸r die 8 Intervalle
	float iv[8]={0};		// Array mit 8 Elementen f¸r die Prozentuale Berechnung

	printf("5.1 Haeufigkeitsverteilung\n\n");

	input(&m, &s);
	count(&i, &m, &n, &s, vektor, &d1, &d2, iv);
	output(vektor, iv, &m, &n, &s);
	

	printf("m...%f s...%f", m, s);
	printf("\n\n\n");		// Nur ein paar Leerzeilen
	system("PAUSE");		// Kommandozeile anhalten
	return 0;	
}