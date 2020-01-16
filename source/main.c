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
#include <RIMS.h>
#endif

enum smP1_States {start, 01_P, 01_R, 10_P, 10_R} smP1_State;

void smP1(){
	switch(smP1_State) {/*Transitions*/
		case start:
			smP1_State = 01_P;
			break;
	
		case 01_P:
			if(A0){
				smP1_State = 01_P;
			}
			else if(!A0){
				smP1_State = 01_R;
			}
			else {
				smP1_State = 01_P;
			}
			break;
	
		case 01_R:
			if(!A0){
				smP1_State = 01_R;
			}
			else if(A0){
				smP1_State = 10_P;
			}
			else{
				smP1_State = 01_R;
			}
			break;
		
		case 10_P:
			if(A0) {
				smP1_State = 10_P;
			}
			else if(!A0){
				smP1_State = 10_R;
			}
			else{
				smP1_State = 01_P;
			}
			break;
	
		case 10_R:
			if(!A0){
				smP1_State = 10_R;
			}
			else if(!A0){
				smP1_State = 01_P;
			}
			else{
				smP1_State = 10_R;
			}
			break;
		default:
			smP1_State = start;
	}
	switch(smP1_State){
		case start:
			break;
	
		case 10_P:
			B0 = 0x01;
			B1 = 0x00;
			break;

		case 10_R:		
			break;
		case 01_P;
			B0 = 0x00;
			B1 = 0x01;
			break;
		case 01_R;
			break;
		default:
			B0 = 0x01;
			B1 = 0x00;
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
