/*
* SPI_UART.c
*/
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL
//////////////////////////////////////////////////////////////////////////
// SPI
//////////////////////////////////////////////////////////////////////////
#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SS PB4
#define SCK PB7
#define MOSI PB5
#define MISO PB6

typedef enum {
	SPI_DIV_4 = 0,
	SPI_DIV_16 = 1,
	SPI_DIV_64 = 2,
	SPI_DIV_128 = 3
} spi_div_t;


void SPI_init_master(uint8_t spi_mode, spi_div_t div) {
	uint8_t tmp;
	uint8_t SPCR_value;

	// Set MOSI, SCK and SS output
	SPI_DDR |= (1<<SS) | (1<<SCK) | (1<<MOSI);
	// Set MISO input
	SPI_DDR &= ~(1<<MISO);
	// Set SS low (active)
	SPI_PORT &= ~(1<<SS);
	// Enable SPI in Master mode
	SPCR_value = (1<<SPE) | (1<<MSTR);


	// Configure SPI mode
	if (spi_mode & 0x02) SPCR_value |= (1<<CPOL);
	if (spi_mode & 0x01) SPCR_value |= (1<<CPHA);
	// Configure SPI clock divider
	SPCR_value |= (div & 0x03);
	// Set SPI Control Register
	SPCR = SPCR_value;

	// Clear SPI Interrupt Flag (SPIF) by reading SPSR and SPDR
	if(SPSR&(1<<SPIF)) {
		tmp = SPSR;
		tmp = SPDR;
	}
	return;
}





//////////////////////////////////////////////////////////////////////////
// UART
//////////////////////////////////////////////////////////////////////////
void UART_init (uint32_t baudrate) {
	uint32_t bdrate;
	bdrate = (F_CPU+baudrate*8)/(baudrate*16)-1;
	UBRRH = (bdrate>>8)&0xFF;
	UBRRL = bdrate&0xFF;

	// Enable Receiver
	UCSRB = (1<<RXEN);

	//Set frame format: 8data, 1stop bit
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}


//Main /////////////////////////////////////////////////////////////////
int main(void) {
	SPI_init_master(0,SPI_DIV_128);
	UART_init(300);


	uint8_t uartempfang=0;


	while(1) {

		// UART abfragen. Falls ein Byte empfangen wurde, dieses über SPI ausgeben
		while(!(UCSRA & (1<<RXC))){					//Auf Bits am Dateneingang warten
			_delay_ms(10); 							// “Last” = andere hier nicht näher betrachtete Programmteile;
		}
		
			
		//Fehler abfragen
		if(UCSRA & ((1<<FE)|(1<<DOR)|(1<<PE) )) return 0xFFFF; //Fehlerfall
		
		//Empfangene Daten als Variable speichern, UDR= Uart Datenregister
		uartempfang=UDR;
		

		//Daten über SPI an Display weitergeben
		SPDR=uartempfang;
		//Fehler aufgetreten?
		if(SPSR & (1<<WCOL)) return 0xFFFF;




		
	}
}
