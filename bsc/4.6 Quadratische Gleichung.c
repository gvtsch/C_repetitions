/***********************************************
# main.c 
# 4.6 Quadratische Gleichung
# 
# Christoph Kempkes HS OS
# Erstellung: 16. Oktober 2012
# Testiert: 18. Oktober 2012
#
# ToDo:
#
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){						// Deklarieren
	double a=0;					
	double b=0;
	double c=0;
	double x1=0;	
	double x2=0;
	double D=0;					// Diskriminante
	

	printf("(a*x)^2 + b*x + c = 0\n");		// Eingabe der Gleichung
	printf("a eingeben:\n");				
	scanf("%lf",&a);
	printf("b eingeben:\n");
	scanf("%lf",&b);
	printf("c eingeben:\n");
	scanf("%lf",&c);

	if ((a==0)&&(b==0)&&(c==0)){								// a = b = c = 0
		printf("a=b=c=0 -> 0=0\n");								// 0 + 0 + 0 = 0
	}

	else if ((a==0)&&(b==0) && (c!=0)){								// a = b = 0 und c != 0
		printf("a=b=0 und c!=0 -> Kann nicht geloest werden\n");	// 0 + 0 +c != 0
	}

	else if ((a==0) && (b!=0)){									// a = 0 und b != 0
		printf("%lf *x + %lf = 0\n", b, c);						// Lineare Gleichung
		x1=(-c)/b;												// b*x + c = 0
		printf("x = %lf\n", x1);
	}

	else if (a!=0){												// a != 0
		printf("%lf *x^2 + %lf *x + c = 0\n", a, b, c);			// Quadratische Gleichung

		D=((b/a)*(b/a))-(4*(c/a));

		if (D<0){												// D < 0 -> Keine Lösung
			printf("Keine Loesung\n");							
		}

		else if (D==0){											// D = 0 -> Eine Lösung
			x1=-(b/(2*a))+((1/2));
			printf("Die Loesung für x ist %lf\n", x1);			
		}

		else if (D>0){											// D > 0 -> Zwei Lösungen
			x1=((-1)*(b/(2*a)))+((sqrt(D))/2);					// x1 berechnen
			x2=((-1)*(b/(2*a)))-((sqrt(D))/2);					// x2 berechnen
			printf("x1 ist %lf\n", x1);							// x1 ausgeben
			printf("x2 ist %lf\n", x2);							// x2 ausgeben
		}
	}


	system("PAUSE");											// Kommandozeile anhalten
	return 0;
}