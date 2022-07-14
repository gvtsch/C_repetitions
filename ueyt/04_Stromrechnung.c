#include <stdio.h>
#include <stdlib.h>

int main () {

	double alt, neu, gg, preis, ust, usterg, betrag, ustbetrag;

	printf("Alter Zaehlerstand in kwH: ");
	scanf("%lf", &alt);
	printf("Neuer Zaehlerstand in khW: ");
	scanf("%lf", &neu);
	printf("Grundegebühr in EUR: ");
	scanf("%lf", &gg);
	printf("Preis pro kwH in EUR: ");
	scanf("%lf", &preis);
	printf("Ust in %%: ");
	scanf("%lf", &ust);

	printf("-----------------------------------------\n");

	usterg = ((ust+100)/(100));
	betrag = (((neu - alt) * preis) + gg) * usterg;
	ustbetrag = (betrag/usterg)*(ust/100);
	
	printf("Rechnungsbetrag inkl. UST EUR %.2lf, davon %.0lf %% Ust: %.2lf\n\n\n", betrag, ust, ustbetrag);


	system("PAUSE");
	return 0;
}