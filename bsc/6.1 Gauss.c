// main.c 
// 6.1 Gauss-Eliminierung
//
// Christoph Kempkes HS OS
// Erstellung vom 16.11.2012
// Testiert am

/*	Gleichungssystem A*x = b (Matrix A und Vektor b sind bekannt / werden angegeben)
	A = L * R (Links untere * rechts obere Dreiecksmatrix)
	=> L * R * x = b	| R * x = y (y = Hilfsvektor) => L * y = b
	
	i - Vorwärtselimination: L * y = b
		Umstellung von A zu Dreiecksmatrix (Stufenform)
		Hilfsvektor y berechen
	ii- Rücksubstitution:	 R * x = y
		LGS lösen
*/

// Bibliotheken laden
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 3	// Maximale Anzahl der Unbekannten



// Eingaben
void eingaben(double a[MAX][MAX], double b[MAX]){
	int i, j = 0;

	// LGS einlesen:
	// A:
	printf("\na11 a12 a13 | b1\na21 a22 a23 | b2\na31 a32 a33 | b3\n\n");
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			printf("a%d%d eingeben... ", i + 1, j + 1);
			scanf("%lf", &a[i][j]);
		}
	}
	// B:
	for(i = 0; i < MAX; i++){
		printf("b%d eingeben... ", i + 1);
		scanf("%lf", &b[i]);
	}
	printf("\n-----\n");

}

// Ausgaben
void ausgaben(double a[MAX][MAX], double b[MAX]){
		
	// Matrix ausgeben:
	printf("Das eingegebene LGS:\n");
	printf("%.2lf	%.2lf	%.2lf	| U1 | %.2lf\n", a[0][0], a[0][1], a[0][2], b[0]);
	printf("%.2lf	%.2lf	%.2lf	| U2 | %.2lf\n", a[1][0], a[1][1], a[1][2], b[1]);
	printf("%.2lf	%.2lf	%.2lf	| U3 | %.2lf\n", a[2][0], a[2][1], a[2][2], b[2]);
	printf("\n----- \n");
	
}

// Ergebnis
void ergebnisausgabe(double b[MAX]){
	int i = 0;
	
	printf("Ergebnis: \n\n");
	for(i = 0; i < MAX; i++){
		printf("U%d... %.3lf\n", i+1, b[i]);}
	
}

// Print Matrix
void print_matrix(double a[MAX][MAX], double b[MAX]){

		printf("\n%.3lf	%.3lf	%.3lf	| U1 | %.3lf\n", a[0][0], a[0][1], a[0][2], b[0]);
		printf("%.3lf	%.3lf	%.3lf	| U2 | %.3lf\n", a[1][0], a[1][1], a[1][2], b[1]);
		printf("%.3lf	%.3lf	%.3lf	| U3 | %.3lf\n", a[2][0], a[2][1], a[2][2], b[2]);
		printf("\n---------------\n");
}

// Berechnung
void berechnen(double a[MAX][MAX], double b[MAX]){
	int i = 1, j = 1, k = 0;
	double x = 0.0, sum = 0.0;

	printf("\nBerechnung:\n\n");
	// Vorwärtselimination
	for(k = 0; k < (MAX - 1); k++){

		for(i = (k + 1); i < MAX; i++){
			x = a[i][k]/a[k][k];
			

			for(j = (k + 1); j < MAX; j++){
				a[i][j] = a[i][j] - a[k][j] * x;
				a[i][k] = 0.0;
				
			}
			b[i] = b[i] - b[k] * x;
		}
		print_matrix(a, b);
	}
	printf("\n"); 
	
	// Resubstitution
	b[MAX-1] = b[MAX-1]/a[MAX-1][MAX-1];
	for(i = (MAX - 2); i >= 0; i--){
		sum = b[i];

		for(j = (i + 1); j < MAX; j++){
			sum = sum - a[i][j] * b[j];
		}
		b[i] = sum / a[i][i];
	} 
}


// Main
int main(){
	
	double a[MAX][MAX];
	double b[MAX];
	
	
	printf("6.1 Gauss-Eliminierung\n\n");
	printf("Anzahl der Gleichungen und Unbekannten MAX = %d\n", MAX);

	eingaben(a, b);
	ausgaben(a, b);
	berechnen(a, b);
	ergebnisausgabe(b);
	


	printf("\n\n\n");
	system("PAUSE");
	return 0;
}