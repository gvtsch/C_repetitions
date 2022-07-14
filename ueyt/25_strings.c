#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int stringlaenge(const char text[]){
	int i;
	
	for (i = 0; text[i] != '\0'; i++);
	return i;
}

void swapchars(char text[], int index1, int index2){
	int i;
	char h;

	for (i = 0; i < stringlaenge(text); i++){
		if(i == index1){
			h = text[i];
			text[i] = text[index2];
			text[index2] = h;
		}
	}
}

int main () {

	char text[300];
	int laenge;

	printf("Text eingeben: ");
	gets(text);

	laenge = stringlaenge(text);
	printf("Der eingegebene Text war %d Zeichen lang\n\n", laenge);

	swapchars(text, 1, 3);
	puts(text);

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}