/*
 * prakt01.c
 *
 * Created: 11.04.2012 08:08:32
 *  Author: tobimaxmicha
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define LED_DDR			DDRA
#define TASTER_DDR		DDRA

#define LED_PORT		PORTA
#define TASTER_PORT		PORTA
#define TASTER_PIN		PINA

#define LED1			(1<<PA0)
#define LED2			(1<<PA1)
#define TASTER			(1<<PA2)


int main(void)
{
	
	uint8_t i=0;
	LED_DDR=LED_DDR|LED1|LED2;
	TASTER_PORT|=TASTER;
	
    while(1)
    {
        if(!(TASTER_PIN & TASTER)) 
		{
				LED_PORT=LED_PORT & ~(LED1|LED2);
				LED_PORT=LED_PORT|i ;
				_delay_ms(3000);
				i++;
				if(i==4)
				i=1;
		
		
		
		}
		
    }
	return (0);
}