// Geschrieben von Christian Hegemann, Tim Baalmann, Thorsten Berghaus



// -------------------------------------------------------------------
// Pseudocode für Frequenzmessung
// MRT-Praktikum
//   ACHTUNG: Im Pseudocode wird auf Bits und Felder direkt zugegriffen.
//            Im wirklichen Code muss dieser Zugriff an die
//            Registerstruktur des Controllers angepasst werden.
// B. Lang, HS-Osnabrueck
// -------------------------------------------------------------------
#define F_CPU 16000000UL

// -------------------------------------------------------------------
// Definitionen und include-Dateien
// -------------------------------------------------------------------
#include <stdint.h>                 // fuer int-Typen fester Wortbreite
#include <stdio.h>                  // fuer "sprintf"-Funktion
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>											//---------------------------------Interrupt

// -------------------------------------------------------------------
// Globale gemeinsame Hilfsvariable
// von Timer1 Input-Capture ISR und Timer1 Overflow ISR
// -------------------------------------------------------------------
static volatile uint8_t  Overflows = 0;  // Ueberlaufzaehler

// -------------------------------------------------------------------
// Globale Variable zur Uebermittlung der Messwerte
// von der Timer1 Input-Capture ISR an main-Programm
// -------------------------------------------------------------------
volatile uint16_t Capture0;         // Zeitstempel bei Start einer Periode
volatile uint16_t Capture1;         // Zeitstempel beim Wechsel in der Periode
volatile uint8_t  Overflows1;       // Ueberlaeufe vom Start bis zum Wechsel
volatile uint16_t Capture2;         // Zeitstempel am Ende der Periode
volatile uint8_t  Overflows2;       // Ueberlaeufe vom Start bis zum Ende
volatile uint8_t  NeueWerteSindDa;  // Marker fuer neue Werte

// -------------------------------------------------------------------
// Timer1 Input-Capture ISR
// (Priorität ist hoeher als Timer 1 Overflow Interrupt)
// -------------------------------------------------------------------
ISR(TIMER1_CAPT_vect) {
  // Interne Hilfsvariable der ISRs
  static uint16_t rising      = 0;  // Zeitstempel bei steigender Flanke
  static uint16_t falling     = 0;  // Zeitstempel bei fallender Flanke
  static uint8_t  fallingOVs  = 0;  // Ueberlaeufe von steigender bis fallender Flanke

  //SPI_DDR |= (1<<SS) | (1<<SCK) | (1<<MOSI);
  if (TCCR1B & (1<<ICES1)) {					// steigende Flanke erkannt
    Capture0 = rising;              // Anfang der Periode
    Capture1 = falling;             // Mitte der Periode
    Overflows1 = fallingOVs;        // Anzahl der Overflows bei der fallenden Flanke
    rising   = ICR1;                // Capture Zählerstand auslesen
    if (TIFR & ~(1<<TOV1)) { // Overflow-Interrupt ist auch angefordert
      if (rising<=0x7fff) {         // Overflow erfolgte vor dem Capture
        Overflows++;                // Overflow noch beruecksichtigen
        TIFR |= (1<<TOV1);
		//TOV1 = 1;                   // Overflow-Interrupt zuruecksetzen               //zuruecksetzen mit 1
                                    // Achtung: Genau im Datenblatt nachlesen,
                                    // wie das Rücksetzen des TOV-Bits funktioniert
      }
    }
    Capture2 = rising;
    Overflows2 = Overflows;         // Anzahl der Overflows bei der steigender Flanke
    NeueWerteSindDa = 1;            // Neue Werte für Hauptschleife markieren
    Overflows = 0;                  // Ueberlaeufe zuruecksetzen
    //ICES1 = 0;
	TCCR1B &= ~(1<<ICES1);                    // nun noch auf fallende Flanke umschalten
  } else {  // fallende Flanke erkannt
    falling = ICR1;                 // Capture Zählerstand auslesen
    if (TIFR & ~(1<<TOV1)) { // Overflow-Interrupt ist auch angefordert
      if (falling<=0x7fff) {        // Overflow erfolgte vor dem Capture
        Overflows++;                // Overflow noch beruecksichtigen
        TIFR |= (1<<TOV1);          // Overflow-Interrupt zuruecksetzen   Reset mit 1
                                    // Achtung: Genau im Datenblatt nachlesen,
                                    // wie das Rücksetzen des TOV-Bits funktioniert
      }
    }
    fallingOVs = Overflows;         // Anzahl der Overflows bei fallender Flanke
    TCCR1B |= (1<<ICES1);           // nun noch auf steigende Flanke umschalten
  }
}

// -------------------------------------------------------------------
// Timer 1 Overflow ISR
// -------------------------------------------------------------------
ISR(TIMER1_OVF_vect) {
  Overflows++;
}
//--------------- SPI iniatilisieren -----------------------------------------
 #define SPI_DDR DDRB
 #define SPI_PORT PORTB

 #define SS PB4		//Slave Select
 #define SCK PB7	//Serial Clock
 #define MOSI PB5	//Master out slave in
 #define MISO PB6	//Slave in Master Out

 typedef enum {		//Nimmet werte zwischen 0-3 an
  SPI_DIV_4   = 0,
  SPI_DIV_16  = 1,
  SPI_DIV_64  = 2,
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
// -------------------------------------------------------------------
// Hauptprogramm
// -------------------------------------------------------------------
int main() {
  uint8_t  Prescale;

  // SPI-Schnittstelle zur Anzeige initialisieren ------------- selbst --------------
  SPI_init_master(0,SPI_DIV_128);
  // Aus letztem Praktikum V4
  //----------------- Buffer init ----------------------------
  char buffer[20];			//Spericher um Daten zu uebertragen
  uint8_t i,bufferidx;


  //---------------------------------------------------------------------------------  -------------------------------------------------------
  // Timer1 Hardware initialisieren
  TCCR1B |= (1<<ICNC1); // Input Capture Rauschunterdrueckung einschalten
  TCCR1B |= (1<<ICES1); // Initial auf steigende Flanke warten
  TCCR1A &= ~((1<<WGM10 ) | (1<<WGM11));
  TCCR1B &= ~((1<<WGM12 ) | (1<<WGM13));
  //WGM(13..10) = 0; // Timer/Counter auf |
  TCCR1B &= ~((1<<CS12) | (1<<CS11));
  TCCR1B |= (1<<CS10);
  //CS(12..10)  = 1; // Prescaling ausgeschaltet, direkt Systemtakt verwenden // 3 bits
  Prescale    = 1; // Prescale-Wert fuer spaetere Rechnung speichern
  TIMSK |= ((1<<TICIE1) | (1<<TOIE1));
  //TICIE1      = 1; // Timer 1 Input-Capture Interrupt freigeben
  //TOIE1       = 1; // Timer 1 Overflow Interrupt freigeben
  sei();          // Interrupts global freigeben

  while(1) {

    // Timer Ereignisse behandeln
    if (NeueWerteSindDa) {
      // Variable für Kopie der Werte der Interrupt Service Routine
      uint16_t Capture0_l;
      uint16_t Capture1_l;
      uint8_t  Overflows1_l;
      uint16_t Capture2_l;
      uint8_t  Overflows2_l;
      // Variable zur Berechnung von Frequenz und Tastverhaeltnis
      uint32_t Periode;
      uint32_t Einsphase;
      uint8_t  Tastverhaeltnis;
      uint16_t Frequenz;

      // Kopien der ISR-Messwerte erstellen
      TIMSK &= ~(1<<TICIE1); // Timer 1 Input-Capture Interrupt sperren
      Capture0_l   = Capture0;
      Capture1_l   = Capture1;
      Overflows1_l = Overflows1;
      Capture2_l   = Capture2;
      Overflows2_l = Overflows2;
      NeueWerteSindDa = 0; // Uebernahme der Werte quittieren
      TIMSK |= (1<<TICIE1); // Timer 1 Input-Capture Interrupt freigeben

      // Aufwaendige Berechnungen (Mehrwortarithmetik) im Hauptprogramm
	    // (siehe Aufgabenblatt)
      Einsphase = (Capture1_l+Overflows1_l*0x10000UL)-Capture0_l;
      Periode = (Capture2_l+Overflows2_l*0x10000UL)-Capture0_l;
      Frequenz = (F_CPU/Prescale)/Periode;
      Tastverhaeltnis = (Einsphase*100)/Periode;

      // Frequenz auf der Anzeige ausgeben
      //(Zeichen '\v' setzt Ausgabeposition auf obere linke Ecke der Anzeige)
	    sprintf(buffer,"\vF: %6u Hz",Frequenz);
		  for(i=0; buffer[i]!='\0'; i++) {
												// Bitte ergaenzen: Zeichen "buffer[i]" ueber SPI an Anzeige ausgeben
			SPDR = buffer[i];
			while(!(SPSR & (1<<SPIF)));			// Ausgeben warten bis Daten übertragen
		  }

      // Tastverhaeltnis auf der Anzeige ausgeben
      //(Zeichen '\n' setzt Ausgabeposition auf Beginn der naechsten Zeile)
      sprintf(buffer,"\nT: %3u %%",Tastverhaeltnis);
		  for(i=0; buffer[i]!='\0'; i++) {

			SPDR = buffer[i];
			while(!(SPSR & (1<<SPIF)));			// Ausgeben warten bis Daten übertragen
		  }
      _delay_ms(500);
    }
  }
  return 0;
}
