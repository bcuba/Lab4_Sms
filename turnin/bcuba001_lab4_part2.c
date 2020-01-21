/*	Author: bcuba001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum smP2_States {start, none, add, sub, both} smP2_State;


void smP1(){
        unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;
	static unsigned char valC;
        switch(smP2_State) {/*Transitions*/
                case start:
                        smP2_State = none;
			valC = 0x07;
                        break;
                case none:
			
                        if(A0 && !A1 && (valC < 10)){
				
				++valC;
				smP2_State = add;
                        }
			else if(A1 && !A0 && (valC >= 0)){	
				--valC;
				smP2_State = sub;
			}
			else if(A0 && A1){
				smP2_State = both;
			}
                        else {
                                smP2_State = none;
                        }
                        break;

                case add:
                        if(A1 && A0){
                                smP2_State = both;
                        }
                        else if(!A1 && !A0){
                                smP2_State = none;
                        }
                        else{
                                smP2_State = add;
                        }
                        break;

                case sub:
                        if(!A1&&!A0) {
                                smP2_State = none;
                        }
	 		else if(A1 && A0){
                                smP2_State = both;
                        }
                        else{
                                smP2_State = sub;
                        }
                        break;

                case both:
                        if(!A0 && A1){
                                smP2_State = sub;
                        }
                        else if(A0 && !A1){
                                smP2_State = add;
                        }
                        else if(!A0 && !A1){
                                smP2_State = none;
                        }
			else{
				smP2_State = both;
			}
                        break;
                default:
                        smP2_State = start;
			break;
        }
        switch(smP2_State){
                case start:
                        break;

                case none:
 	                break;

                case add:			
                        break;
                case sub:
                        break;
                case both:
			valC = 0x00;
                        break;
                default:
			valC = 0x07;
                        break;
        }
	
	PORTC = valC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00;
        PORTA = 0xFF;
        DDRC = 0xFF;
        PORTC = 0x00;
        smP2_State = start;
    /* Insert your solution below */
   while (1) {
        smP1();
    }
    return 1;
}


