#include <stdio.h>
#include <stdlib.h>

int ziffernsumme(int zahl1){
	int summe = 0;
	while(zahl1){
		summe += zahl1%10;
		zahl1/=10;
	}
	return summe;
}

int main () {

	int zahl = 2354627;
	int zahl1 = 235462;
	int i = 0;
	int pz = 0;
	
	while(zahl1){
		i++;
		if(i%2 == 0){
			pz += ziffernsumme (2*(zahl1%10));
		}else{
			pz += zahl1%10;
		}
		zahl1/=10;
	}
	pz%=10;

	if(zahl%10 == pz) {
		printf("Die PZ war richtig.");
	}else{
		printf("Falsch");
	}


	printf("\n\n\n");
	system("PAUSE");
	return 0;
}