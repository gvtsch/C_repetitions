// main.c
// 5.2 Palindrom
//
// Christoph Kempkes HS OS
// Erstellt am 23. Okt. 2012
// Testiert am 01. Nov. 2012
// ToDo:

// Bibliotheken laden
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



int main(){
	
	char a[255], b[255];	// a und b mit max 255 Feldern
	int length, i, j, k; 

	
	printf("5.2 - Palindrom\n\n\n");

	printf("Text eingeben (Max. 255 Zeichen): ");
	scanf("%[^\n]", a);
	

	i = 0;
	j = 0;
	length = 0;

	// Buchstabe?!
	for (i=0; a[i] != '\0'; i++) {		// Solange das Ende des Textes nicht erreicht ist:
		if (a[i] >= 65 && a[i] <= 90) {		// a[i] = Großbuchstabe?
			b[j] = a[i] + 32;		// dann in b[j] ablegen und 32 addieren, damit Kleinbuchstabe
			length++;		// Länge + 1
			j++;	// j + 1
		} 
		else if (a[i] >= 97 && a[i] <= 122) {	// a[i] = Kleinbuchstabe?
			b[j] = a[i];	// dann in b[j] ablegeb
			length++;
			j++;
		}
	} 
		
	b[j] = '\0';
	printf("Die Laenge des Textes: %d\n", length);	
	printf("Text in Kleinbuchstaben und ohne Sonderzeichen lautet: %s\n", b);


	// Prüfung auf Palindrom
	k = 0;	// Fehlervariable auf 0 setzen
	for (i=0; i<(length/2); i++) {		// Solange i kleiner ist als der Text/2 lang ist
		if (b[i]!= b[length-1-i]) {		// z.B. Länge = 13 -> b[0] == b[12]? Erster gleich dem letzten Buchstaben?
			// length--;
	//	}
		//else {
		//length--;
		k++;		// Wenn sich 2 überprüfte Buchstaben nicht gleich sind dann k+1
		}
	}

	if (k == 0) {		// Nur Übereinstimmungen in der vorherigen Überprüfung
		printf("\n%s ist ein Palindrom.\n", b);
	}
	else {		// Wenigstens ein Fehler
		printf("\n%s ist KEIN Palindrom.\n", b);
	}

	

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}