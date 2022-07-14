/***********************************************
# main.c 
# 4.4 Schaltjahr
# 
# Christoph Kempkes HS OS
# Erstellung: 10. Oktober 2012
# Testiert: 11.10.2012
#
# ToDo:
#
************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(){

int j;												// Variable j als ganze Zahl definieren

	printf("Jahreszahl eingeben:\n");				// Aufforderung zum Eingeben der Jahreszahl
	scanf("%d", &j);								// Eingabe der Jahreszahl

		if (((j%4)==0) && ((j%100)!=0))	{			// Ist die Jahreszahl durch 4 restlos teilbar und nicht (!) durch 100?
			printf("%d ist ein Schaltjahr.\n",j);	// Ausgabe
										}

		else if ((j%400)==0){						// Oder ist die Jahreszahl restlos durch 400 teilbar?
			printf("%d ist ein Schaltjahr.\n",j);	// Ausgabe
							}

		else	{
			printf("%d ist kein Schaltjahr.\n",j);	// Die Jahreszahl ist kein Schaltjahr - Ausgabe	
				}
		system("PAUSE");							// Kommandozeile anhalten
		return 0;
								
}