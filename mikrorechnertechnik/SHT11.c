//--------- /* Kommunikation mit SHT11 */ ---------
//----------------------------------------------
// Funktion:	Protokoll für Feuchtesensor SHT11
// 			Linearisierung Druck u. Tenperatur	
//			CRC Berechnung für Kommunikation mit SHT11
//			Lesen / Schreiben Statusregister SHT11
//	
//----------------------------------------------
// Datum:			18.09.2008
// Autor:			Sebastian Bierwirth
//----------------------------------------------

#include "sht11.h"
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#define sb(byte,bit) (byte) |= (1<<(bit)) //setze Bit
#define cb(byte,bit) (byte) &= ~(1<<(bit)) //lösche Bit
#define DATA(i) if (i) sb(SHT11_PORT_DATA,SHT11_PC_DATA); else cb(SHT11_PORT_DATA,SHT11_PC_DATA)
#define SCK(i)  if (i) sb(SHT11_PORT_SCK,SHT11_PC_SCK); else cb(SHT11_PORT_SCK,SHT11_PC_SCK)
#define setREAD      cb(SHT11_DDR_DATA,SHT11_PC_DATA)//; sb(SHT11_PORT_DATA,SHT11_PC_DATA)
#define setWRITE     sb(SHT11_DDR_DATA,SHT11_PC_DATA)

#define noACK 0
#define ACK   1
                            //adr  command  r/w
#define STATUS_REG_W 0x06   //000   0011    0
#define STATUS_REG_R 0x07   //000   0011    1
#define MEASURE_TEMP 0x03   //000   0001    1
#define MEASURE_HUMI 0x05   //000   0010    1
#define RESET        0x1e   //000   1111    0

enum {TEMP,HUMI};

volatile unsigned char crc=0;


void s_transstart(void)
// Start Sequenz
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{  	
	DATA(1); SCK(0);				
	_delay_us(1);
	SCK(1);
	_delay_us(1);
	DATA(0);
	_delay_us(1);
	SCK(0);
	_delay_us(5);
	SCK(1);
	_delay_us(1);
	DATA(1);         
	_delay_us(1);
	SCK(0);	
}


char s_write_byte(unsigned char value)
// ein Byte an den Sensor senden und Ack abwarten
{ 
	unsigned char i,error=0;
	setWRITE;
	for (i=0x80;i>0;i/=2)       
	{ 
		if (i & value) 
		{
			DATA(1);          	
			calc_checksum(1);
		}
		else
		{
			DATA(0);
			calc_checksum(0);
		}
		SCK(1);                 
		_delay_us(5);
		SCK(0);
	}
	setREAD;       				// auf Eingang
	SCK(1);                    	// Takt für Ack
	_delay_us(2);
	error=(SHT11_PIN_DATA & (1 << SHT11_PC_DATA)); 	// Ack abwarten 
	_delay_us(2);
	SCK(0);
    return error;               // wenn kein Ack -> Error
}


char s_read_byte(unsigned char ack)
// ein Byte vom Sensor empfangen und ggf. Ack senden
{ 
	unsigned char i,val=0;
	
	setREAD; // auf Eingang
	
	for (i=0x80;i>0;i/=2)		
	{	
		SCK(1);                 
		if (SHT11_PIN_DATA & (1 << SHT11_PC_DATA))
		{ 
			val=(val | i);
			calc_checksum(1);
		}
		else calc_checksum(0);
		SCK(0);
	}
	
	setWRITE;       			// auf Ausgang
  
	if (!ack) DATA(1);
	else DATA(0);
	SCK(1);                     // Takt für Ack
	_delay_us(5);
	SCK(0); 
	return val;
}


void s_connectionreset(void)
// Reset Sequenz
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{  
	unsigned char i; 
	
	setWRITE;
	DATA(1);SCK(0);					
	
	for(i=0;i<9;i++)                //9 Takt Zyklen
	{ 
		SCK(1);
		SCK(0);
	}
	s_transstart();                   // Start Sequenz
}

char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum)
// Statusregister und Checksumme lesen
{ 
	unsigned char error=0;
	error+=s_read_statusreg_crc((unsigned char*) &crc);
	s_transstart();                   // Start Sequenz
	error+=s_write_byte(STATUS_REG_R); // Befehl für Statusr. lesen senden
	*p_value=s_read_byte(ACK);		  // Register lesen (8bit)
	*p_checksum=s_read_byte(noACK);   // Checksumme lesen (8-bit) 
	return error;                     // wenn keine Antwort vom Sensor -> Fehler
}

char s_write_statusreg(unsigned char *p_value)
// Statusregister schreiben
{ 
	unsigned char error=0;
	s_transstart();                   // Start Sequenz
	error+=s_write_byte(STATUS_REG_W);// Befehl für Statusr. schreiben senden
	error+=s_write_byte(*p_value);    // Register schreiben
	return error;                     // wenn keine Antwort vom Sensor -> Fehler
}


char s_measure(unsigned char *p_value, unsigned char *p_crc_recieved, unsigned char *p_crc_calculated, unsigned char mode)
// Messung mit Checksumme
{ 
	unsigned error=0;
	error+=s_read_statusreg_crc((unsigned char*) &crc);
	s_transstart();       // Start Sequenz
	switch(mode)
	{                     //Befehl für jeweilige Messung senden
		case TEMP   : error+=s_write_byte(MEASURE_TEMP); break;
		case HUMI   : error+=s_write_byte(MEASURE_HUMI); break;
		default     : break;    
	}
	
	setREAD; // Data auf Eingang
  
	while (1)
	{
		if(!(SHT11_PIN_DATA & (1 << SHT11_PC_DATA))) break; // warten bis Messung beendet
	}
    
	if(SHT11_PIN_DATA & (1 << SHT11_PC_DATA)) error+=1;                
	
	*(p_value+1)  =s_read_byte(ACK);    // MSB lesen
	*(p_value)=s_read_byte(ACK);    // LSB lesen
	*p_crc_calculated = crc;
	*p_crc_recieved =s_read_byte(noACK);  // Checksum lesen
	*p_crc_recieved = retrieve_char(*p_crc_recieved);
	return error;
}


void calc_sth11(double *p_humidity ,double *p_temperature)
// Temperatur und Feuchte berechnen
{ 
	const double C1=-4.0;              // fuer 12 Bit
	const double C2=+0.0405;           // fuer 12 Bit
	const double C3=-0.0000028;        // fuer 12 Bit
	const double T1=+0.01;             // fuer 14 Bit @ 5V
	const double T2=+0.00008;          // fuer 14 Bit @ 5V   

	double rh=*p_humidity;             
	double t=*p_temperature;           
	double rh_lin;                    
	double rh_true;                   
	double t_C;                        

	t_C=t*0.01 - 40;                  
	rh_lin=C3*rh*rh + C2*rh + C1;     
	rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   
	if(rh_true>100)rh_true=100;       
	if(rh_true<0.1)rh_true=0.1;      
	
	*p_temperature=t_C;               
	*p_humidity=rh_true;              
}


double calc_dewpoint(double h,double t)
// Taupunkt berechnen
{ 
	double logEx,dew_point;
	logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);
	dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
	return dew_point;
}

void calc_checksum(char bit)
{
	if ((bit && (crc >= 128)) || (!bit && (crc < 128))) // wenn empfangenes Bit = Bit 7 von CRC
	{
		crc*=2;	// shift crc
	}
	else 
	{
		crc*=2; // shift crc
		crc++;  // Bit 1 = 1
		crc ^= (1<<4)^(1<<5); // Bit 4 und Bit 5 invertieren
	}
}

unsigned char retrieve_char(char in)
{
	in = (( in << 1) & 0xaa) | (( in >> 1) & 0x55);
	in = (( in << 2) & 0xcc) | (( in >> 2) & 0x33);
	in = (( in << 4) & 0xf0) | (( in >> 4) & 0x0f);
	return in;
}


char s_read_statusreg_crc(unsigned char *p_crc)
// Statusregister lesen und Wandlung zur Checksummenbildung
{ 
	unsigned char error=0, tmp;
	s_transstart();                   
	error=s_write_byte(STATUS_REG_R); 
	*p_crc=s_read_byte(ACK);		  	
	crc=retrieve_char(crc);
	tmp = crc&0xf0;
	s_read_byte(noACK);		
	crc=tmp;	
	return error;               	
}
