#include "SHT.h"
#include <util/delay.h>


//----------------------------------------------------------------------------------------
float SHT_raw_to_physical_temp(unsigned int raw_temp)
//----------------------------------------------------------------------------------------
// calculates temperature [C] 
{ 
return (0.01*raw_temp - 40); 
}

//----------------------------------------------------------------------------------------
float SHT_raw_to_physical_rh(unsigned int raw_rh)
//----------------------------------------------------------------------------------------
// calculates relative humidity [%] 
{ 
return (-4.0 + 0.0405*raw_rh - 0.0000028*raw_rh*raw_rh); 
}



//----------------------------------------------------------------------------------------
void SHT_init(void)
//----------------------------------------------------------------------------------------
{
	SHT_DATA_INPUT;//Data (PD6) auf Eingang (receive)
	SHT_DDR |= (1<<SHT_CLK); //CLK (PD7) auf Ausgang -->AVR ist Master
}


//----------------------------------------------------------------------------------------
void SHT_start_trans(void)
//----------------------------------------------------------------------------------------
{	
	unsigned char cnt;

	SHT_DATA_HIGH;				// clear Interface FSM inside SHT
	for (cnt=0;cnt<20;cnt++) { //20 Taktzyklen ausgeben (20 us pro Takt)
		SHT_CLK_HIGH;
		SHT_CLK_LOW;
		}
    //das ist dann wohl das Start-Signal
	SHT_CLK_HIGH;	
	SHT_DATA_LOW;	
	SHT_CLK_LOW;	
	SHT_CLK_HIGH;	
	SHT_DATA_HIGH;
	SHT_CLK_LOW;	
}



//----------------------------------------------------------------------------------
unsigned char SHT_write_byte(unsigned char SHT_value)
//----------------------------------------------------------------------------------
{
	unsigned char error=0;

    for(unsigned char bit=8; bit>0; bit--){//Jedes Bit einzeln durchjagen
	//bit-1=7...0 for(bit=7;bit<=0;bit--) falsch, da 0-1=255
	//alternative: anderer datentyp

        if(SHT_value & (1<<(bit-1))){ SHT_DATA_HIGH} //wenn eine 1 anliegt: data auf High
        else {SHT_DATA_LOW} //sonst: Data auf Low
        
        SHT_CLK_HIGH //Taktsignal
        SHT_CLK_LOW
    }

	SHT_DATA_INPUT//Data auf input setzen, um ACK einlesen zu koennen

    SHT_CLK_HIGH  //CLK auf 1
    error=SHT_DATA_IN;//ACK einfangen(0, falls ACK gesendet, sonst 1
    SHT_CLK_LOW      //und CLK wieder auf "low" setzen"

	return error;
}



//----------------------------------------------------------------------------------
unsigned char SHT_read_byte(unsigned char ack)
//----------------------------------------------------------------------------------
{
	unsigned char val=0;

    for(unsigned char bit=8; bit>0; bit--){//Bit fuer Bit einlesen
        SHT_CLK_HIGH //CLK auf high
        if(SHT_DATA_IN) val|=(1<<(bit-1));//wenn Data auf High: einlesen
        SHT_CLK_LOW//CLK wieder auf Low
    }

    if(ack){ SHT_DATA_LOW }//ACk senden, falls verlangt
    else{ SHT_DATA_HIGH }//sonst kein ACK senden
    SHT_CLK_HIGH//Takt ausgeben
    SHT_CLK_LOW

	return val;
}


//----------------------------------------------------------------------------------
unsigned char SHT_measure(float *temperature, float *humidity)
//----------------------------------------------------------------------------------
{

	unsigned char cst,csrh,err,sreg;
	unsigned int t_raw,rh_raw;

	SHT_init();

	// Set and check Status Register

	SHT_start_trans();                          //starte neue transmission

	err = SHT_write_byte  (SHT_CMD_WR_STATUS);  //Command: write status register
	if (err) return(SHT_ERROR_NO_ACK);          //ACK

	err = SHT_write_byte  (SHT_SR_DEFAULT);     //set status register on default (0000 0000)
	if (err) return(SHT_ERROR_NO_ACK);          //ACK

	SHT_start_trans();
	err  = SHT_write_byte (SHT_CMD_RD_STATUS);  //Command: read status register
	if (err) return(SHT_ERROR_NO_ACK);          //ACK

	sreg = SHT_read_byte  (SHT_ACK);            //read status register
	if (sreg != SHT_SR_DEFAULT) return(SHT_ERROR_SR_CHECK);//status register on default?

	// Temperature Measurement

	SHT_start_trans();                          //starte neue transmission

	err = SHT_write_byte (SHT_CMD_RD_TEMPERATURE);  //Command: read temperature
	if (err) return(SHT_ERROR_NO_ACK);              //ACK

	SHT_DATA_INPUT;//Auf Eingang schalten
	while (SHT_DATA_IN) _delay_us(1);//warten, bis Messung beendet

	t_raw   = SHT_read_byte(SHT_ACK);//die ersten (8?) Bit auslesen
	t_raw <<= 8;                     //und nach hinten schieben
	t_raw  |= SHT_read_byte(SHT_ACK);//die letzten (6?) Bit auslesen und dran haengen
	cst 	= SHT_read_byte(SHT_NO_ACK);//Kein ACK senden, checksumm einlesen???

	*temperature	= SHT_raw_to_physical_temp(t_raw);//in °C umwandeln

	// Humidity Measurement

	SHT_start_trans();                          //starte neue transmission

	err = SHT_write_byte (SHT_CMD_RD_HUMIDITY); //Command: read humidity
	if (err) return(SHT_ERROR_NO_ACK);          //ACK

	SHT_DATA_INPUT;                             //Auf Eingang setzen
	while (SHT_DATA_IN) _delay_us(1);           //Ende der Messung abwarten

	rh_raw  = SHT_read_byte(SHT_ACK);           //Die ersten (8?) Bit einlesen
	rh_raw<<= 8;                                //und nach hinten schieben
	rh_raw |= SHT_read_byte(SHT_ACK);//die letzten (4?) Bit einlesen und dran packen
	csrh 	= SHT_read_byte(SHT_NO_ACK);////Kein ACK senden, checksumm einlesen???

	*humidity	= SHT_raw_to_physical_rh(rh_raw);//in % umrechnen

	return (SHT_ERROR_NO_ERROR);
}


//----------------------------------------------------------------------------------
void SHT_float_to_int(float fl, int *integer, int *fract)
//----------------------------------------------------------------------------------
{
	*integer = fl;
	*fract	 = (fl*100)-(*integer*100);
}

