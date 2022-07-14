#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "MPX.h"

unsigned int MPX_ADC(void)
{
	unsigned long AirPress=0;

	if(ADMUX!=0x41) ADMUX=(1<<REFS0)|(1<<MUX0);//AREF=AVCC, ADC1 Single Ending Input
	if(ADCSRA!=0x87) ADCSRA=0x87; //ADEN, ADPS2:0 --> Wandler ein und Prescaler 111

	ADCSRA|=(1<<ADSC); //AD-Wandlung starten

	while(ADCSRA & (1<<ADSC)); //warten bis AD-Wandlung beendet

	AirPress = ADCH&3; // Bit 8 und 9 lesen
	AirPress<<=8;	//schieben
	AirPress|=ADCL; //Bit 0 bis 7 lesen

	AirPress = (AirPress*51)/47 + 105;//P=((ADC*Vref)/1024)*100000/(Vs*10*9)+105 = ADC*500000/470016 + 105



	return ((int)AirPress);
}
