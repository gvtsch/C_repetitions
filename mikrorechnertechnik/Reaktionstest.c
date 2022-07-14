#include <avr/io.h>     //fuer DDR, PORT und PIN
#include <util/delay.h> //fuer _delay_ms()
//#include <stdio.h>      //fuer fprintf()? (kompiliert auch ohne)
#include <stdlib.h>     //fuer srand() und rand()

#include "libmrt.h"     //fuer KL(), BeepOn() etc.

#define Tast_DDR     DDRC       //Datenrichtungsregister fuer Taster
#define Tast_PIN     PINC       //PIN fuer Taster

#define Taste1       (1<<PC0)   //Portbits fuer Taster
#define Taste2       (1<<PC1)

//#define MEHRSPIELER 0   //Einstellung fuer Einzel- oder Mehrspielermodus

#define BEEPTIME 500    //Wie lange der Signalton dauern soll [ms]

int tasteGedrueckt(){   //ermittelt ob und wenn ja, welcher Taster gedrueckt wurde
    
    // 0 == keiner, 1 == Taster1, 2 == Taster2, 3 == beide Taster
    return(((~Tast_PIN)&Taste1)   ?   (((~Tast_PIN)&Taste2) ? 3 : 1)   :   (((~Tast_PIN)&Taste2) ? 2 : 0));
    //Annahme: Wenn Taster gedrueckt, dann logische '1' an PINC
}

int main(){
    
    uint16_t reaktionsZeit=0;   //Zeit bis Taste gedrueckt 0 - 3000 ms  --> 16 Bit
    uint8_t sieger=0; //Speichert, wer im Mehrspieler-Modus gewonnen hat.
    //uint8_t mehrspieler=0; //Einstellung fuer Einzel- oder Mehrspielermodus

    InitMRTBoard();

    Tast_DDR &= (~(Taste1|Taste2)); //Taster-Portbits auf Eingang
    PORTC |= (Taste1|Taste2);     //Pull-Up-Widerstaende fuer PC0 und PC1 aktivieren

    fprintf(_LCD,"\fDruecken Sie Taster 1 fuer Einzelspieler- oder Taster 2\nfuer Mehrspielermodus.\n");

    while(!(mehrspieler=tasteGedrueckt())); //Warten auf Modus-Wahl
    mehrspieler = (mehrspieler==1) ? 0 : 1; //Modus-Wahl ermitteln
    if(mehrspieler) fprintf(_LCD,"\fSie haben den Mehrspielermodus gewaehlt!\n");
    else fprintf(_LCD,"\fSie haben den Einzelspielermodus gewaehlt!\n");
    _delay_ms(2000); //2s warten



    while (1){
        
        fprintf(_LCD,"\fNeues Spiel!\n"); //LCD loeschen, neues Spiel starten

        _delay_ms((rand()%8001)+2000); //2 bis 10s warten


        if(tasteGedrueckt())    //Wenn Taste gedrueckt, obwohl LED noch aus:
            fprintf(_LCD, "Trottel!\n");    //Fehlermeldung


        else{                   //sonst:

            KL(0xFF);           //LED an
            BeepOn();           //Signalton an
            

//                                  ---Einzelspieler-Modus---

            if(!mehrspieler){
                
                for(reaktionsZeit=0; reaktionsZeit<=3000; ++reaktionsZeit){
                //for-Schleife zaehlt die ms, bis gedrueckt wurde, oder die Zeit um ist
                    
                    _delay_ms(1);   //Aufloesung: 1ms
                    if(reaktionsZeit==BEEPTIME) BeepOff();   //Signalton aus nach 0.5s
                    if(tasteGedrueckt()) break; //Wenn irgendeine Taste gedrueckt => for-Schleife verlassen
                }

                //Es wurde rechtzeitig gedrueckt. Reaktionszeit ausgeben. (+1, weil die letzte ms nicht mitgezaehlt wurde)
                if(reaktionsZeit<=3000){
                    if(reaktionsZeit<BEEPTIME) BeepOff();    //Falls Signalton noch an: ausschalten
                    fprintf(_LCD,"Reaktionszeit: %ums\n", reaktionsZeit+1);
                    srand(reaktionsZeit);   //Zufallszahlen-Generator neu initialisieren
                }
                
                else fprintf(_LCD,"LOOSER!\n"); //Es wurde nicht, bzw. zu spaet gedrueckt.
            }


//                                  ---Mehrspieler-Modus---

            else{
                for(reaktionsZeit=0; reaktionsZeit<=3000; ++reaktionsZeit){
                //for-Schleife zaehlt die ms, bis gedrueckt wurde, oder die Zeit um ist
                    
                    _delay_ms(1);   //Aufloesung: 1ms
                    if(reaktionsZeit==BEEPTIME) BeepOff();   //Signalton aus nach 0.5s
                    if((sieger=tasteGedrueckt())) break;//Wenn irgendeine Taste gedrueckt => for-Schleife verlassen
                    //gleichzeitig wird in "sieger" gespeichert, welcher Spieler (zuerst) gedrueckt hat
                }

                if(reaktionsZeit<BEEPTIME) BeepOff();    //Falls Signalton noch an: ausschalten


                //unentschieden
                if(sieger==3){
                    fprintf(_LCD,"\fUnentschieden!\n%ums\n", reaktionsZeit+1);
                    srand(reaktionsZeit);   //Zufallszahlen-Generator neu initialisieren
                }
                //Es giebt einen Sieger
                else if(sieger){
                    fprintf(_LCD,"\fSpieler %u\n%ums\n", sieger, reaktionsZeit+1);
                    srand(reaktionsZeit);   //Zufallszahlen-Generator neu initialisieren
                }
                //Beide waren zu langsam
                else fprintf(_LCD,"\fLOOSER");
            }

//                               ---ENDE Mehrspieler-Modus---

            KL(0x0);//LED´s aus
            _delay_ms(2000);//2s warten
        }//of else (!tasteGedrueckt())
    }//of while(1)

    return 0;
}
