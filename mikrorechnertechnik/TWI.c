#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

//----------------------------------------------------------------------------------------
void TWI_init (void)
//----------------------------------------------------------------------------------------
// Initialize TWI 
{
	PORTC |= 3;
	TWSR = 2; 								// Prescaler = 16
	TWBR = 50;								// approx 10kHz SCL clock
	TWCR = (1<<TWEN);
}

//----------------------------------------------------------------------------------------
void TWI_off (void)
//----------------------------------------------------------------------------------------
// Switch TWI off
{
	TWCR = 0;
}

//----------------------------------------------------------------------------------------
unsigned char TWI_start (void)
//----------------------------------------------------------------------------------------
// Transmit Start Code
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Start condition = 1
	while (!(TWCR & (1<<TWINT)));			// wait for TWINT=1
	TWCR = 1 << TWEN;                       // Start Condition = 0
	return (TWSR&0xf8);
}

//----------------------------------------------------------------------------------------
void TWI_stop (void)
//----------------------------------------------------------------------------------------
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);// Stop condition
}

//----------------------------------------------------------------------------------------
unsigned char TWI_addr (unsigned char addr, unsigned char readflag)
//----------------------------------------------------------------------------------------
// Transmit Addr
//readflag == TW_WRITE oder TW_READ
{
	TWDR = (addr<<1)|readflag;
	TWCR = (1<<TWINT)|(1<<TWEN);;		
	while (!(TWCR & (1<<TWINT)));			// wait for TWINT=1
	return (TWSR&0xf8);
}

//----------------------------------------------------------------------------------------
unsigned char TWI_tx_data (unsigned char data)
//----------------------------------------------------------------------------------------
// Transmit Data
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));			// wait for TWINT=1	
	return (TWSR&0xf8);
}

//----------------------------------------------------------------------------------------
unsigned char TWI_rx_data (unsigned char *data, unsigned char snd_ack)
//----------------------------------------------------------------------------------------
// Receive Data
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(snd_ack<<TWEA);
	while (!(TWCR & (1<<TWINT)));			// wait for TWINT=1
	*data = TWDR;
	return (TWSR&0xf8);
}





//----------------------------------------------------------------------------------------
unsigned char TWI_rx (unsigned char addr, 
					  unsigned char reg, 
					  unsigned char *data, 
					  unsigned char num_data)
//----------------------------------------------------------------------------------------
// Connect to TWI Slave and receive data
// addr: 		slave address
// reg:  		register to access
// data:		pointer to data
// num_data:	number of data to receive
// return val:	status as received from TWI module ; zero if no error occured
{
 
    TWI_start();//sende start
    if(TW_STATUS!=TW_START) return TW_STATUS;//start uebertragen?

    TWI_addr(addr, TW_WRITE);//sende Bausteinaddresse und schreiben
    if(TW_STATUS!=TW_MT_SLA_ACK) return TW_STATUS;//angekommen?

    TWI_tx_data(reg);//sende Register-Addresse
    if(TW_STATUS!=TW_MT_DATA_ACK) return TW_STATUS;//angekommen?

    TWI_start();//sende repeated start
    if(TW_STATUS!=TW_REP_START && TW_STATUS!=TW_START) return TW_STATUS;//angekommen?

    TWI_addr(addr, TW_READ);//sende Bausteinregister und lesen
    if(TW_STATUS!=TW_MR_SLA_ACK) return TW_STATUS;//angekommen?

    for(unsigned char received=0; received<num_data-1;received++){
        TWI_rx_data(&data[received],1);//empfange Datum
        if(TW_STATUS!=TW_MR_DATA_ACK) return TW_STATUS;//Datum empfangen und ACK gesendet?
    }

	TWI_rx_data(&data[num_data-1],0);//das letzte Byte empfangen, ohne ein ACK zu senden
	if(TW_STATUS!=TW_MR_DATA_NACK) return TW_STATUS;
    
    
    TWI_stop();//sende stop
    return (0);
}


//----------------------------------------------------------------------------------------
unsigned char TWI_tx (unsigned char addr, 
					  unsigned char reg, 
					  unsigned char *data, 
					  unsigned char num_data)
//----------------------------------------------------------------------------------------
// Connect to TWI Slave and transmit data
// addr: 		slave address
// reg:  		register to access
// data:		pointer to data
// num_data:	number of data to transmit
// return val:	status as received from TWI module ; zero if no error occured
{

    TWI_start();//sende start
    if(TW_STATUS!=TW_START) return TW_STATUS;//angekommen?

    TWI_addr(addr, TW_WRITE);//sende Bausteinaddresse und schreiben
    if(TW_STATUS!=TW_MT_SLA_ACK) return TW_STATUS;//angekommen?

    TWI_tx_data(reg);//sende 1. zu lesendes Register des Bausteins
    if(TW_STATUS!=TW_MT_DATA_ACK) return TW_STATUS;//angekommen?

    for(unsigned char transmitted=0; transmitted<num_data; transmitted++){
        TWI_tx_data(data[transmitted]);//Datum senden
        if(TW_STATUS!=TW_MT_DATA_ACK) return TW_STATUS;//angekommen?
    }
 return (0);
}






