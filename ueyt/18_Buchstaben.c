#include <stdio.h>
#include <stdlib.h>

int istBuchstabe(int ch);

int main () {

	int ch;

	while((ch = getchar()) != EOF){
		putchar(istBuchstabe(ch));
	}

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}

int istBuchstabe(int ch){
	if (ch >=65 && ch <= 90){
		return 1;
	}
	else if(ch >= 97 && ch <= 122){
		return 1;
	}
	else
		return ch;
}