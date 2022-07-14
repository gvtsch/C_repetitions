#include <stdio.h>
#include <stdlib.h>

int ausgabe(int z);

int main () {

	int z;

	printf("Geben sie eine Zahl ein: ");
	scanf("%d", &z);
	printf("%d", ausgabe(z));
	



	printf("\n\n\n");
	system("PAUSE");
	return 0;
}

int ausgabe(int z){

	z /=5;
	return z;

}