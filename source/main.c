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

enum smP1_States {start, B0_P, B0_R, B1_P, B1_R} smP1_State;

void smP1(){
        unsigned char A0 = PINA;
        switch(smP1_State) {/*Transitions*/
                case start:
                        smP1_State = B0_P;
                        break;

                case B0_P:
                        if(A0){
                                smP1_State = B0_P;
                        }
                        else if(!A0){
                                smP1_State = B0_R;
                        }
                        else {
                                smP1_State = B0_P;
                        }
                        break;

                case B0_R:
                        if(!A0){
                                smP1_State = B0_R;
                        }
                        else if(A0){
                                smP1_State = B1_P;
                        }
                        else{
                                smP1_State = B0_R;
                        }
                        break;

                case B1_P:
                        if(A0) {
                                smP1_State = B1_P;
                        }
		else if(!A0){
                                smP1_State = B1_R;
                        }
                        else{
                                smP1_State = B1_P;
                        }
                        break;

                case B1_R:
                        if(!A0){
                                smP1_State = B1_R;
                        }
                        else if(!A0){
                                smP1_State = B0_P;
                        }
                        else{
                                smP1_State = B1_R;
                        }
                        break;
                default:
                        smP1_State = start;
        }
        switch(smP1_State){
                case start:
                        break;

                case B0_P:
                        PORTB = 0x01;
                        break;

                case B0_R:
                        break;
                case B1_P:
                        PORTB = 0x02;
                        break;
                case B1_R:
                        break;
                default:
                        PORTB = 0x01;
                        break;
        }
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00;
        PORTA = 0xFF;
        DDRB = 0xFF;
        PORTB = 0x00;
        smP1_State = start;
    /* Insert your solution below */
                   while (1) {
        smP1();
    }
    return 1;
}
                                                                                                                                                                                                       102,1         91%

