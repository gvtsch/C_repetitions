#include <stdio.h>
#include <stdlib.h>

int expon(int basis, int hoch){

	if (hoch < 0){
		return 0;
	}
	else if (hoch == 0){
		return 1;
	}
	else return basis*expon(basis, (hoch - 1));

}

int main () {

	int basis, hoch, ergebnis;

	hoch=0;

	printf("Basis...");
	scanf("%d", &basis);
	printf("Exponent...");
	scanf("%d", &hoch);
	ergebnis = expon(basis, hoch);
	printf("%d", ergebnis);


	printf("\n\n\n");
	system("PAUSE");
	return 0;
}