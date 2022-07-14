#include <stdio.h>
#include <stdlib.h>
#define G 1000

void befuelleFeld(int feld[], int lang){
	int i;
	
	for(i = 0; i < lang; i++){
		feld[i] = i;
	}
}

void printFeld(int feld[], int lang){
	int i;

	for(i = 0; i < lang; i++){
		printf("%4d", feld[i]);
	}
}

void groessteZahl(int feld[], int lang){
	int i;
	int max;

	max = feld[0];

	for(i = 0; i < lang; i++){
		if(feld[i] > max){
			max = feld[i];
		}
	}
	printf("\nDie groesste Zahl ist %d", max);
}




int main () {

	int feld[G] = {0};
	befuelleFeld(feld, G);
	printFeld(feld, G);
	groessteZahl(feld, G);

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}