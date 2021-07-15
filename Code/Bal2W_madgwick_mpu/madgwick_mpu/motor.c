/*
 * motor.c
 *
 * Created: 12-08-2019 3.11.07 PM
 *  Author: PRANAYJUNARE
 */ 


#include "motor.h"

void forward(uint8_t sleft,uint8_t sright){
	sbit(PORTD,0);
	cbit(PORTD,1);
	sbit(PORTA,0);
	cbit(PORTA,1);
	sbit(PORTC,7);
	OCR1A=sleft;
	OCR1B=sright;
}

void backward(uint8_t sleft,uint8_t sright){
	sbit(PORTD,1);
	cbit(PORTD,0);
	sbit(PORTA,1);
	cbit(PORTA,0);
	cbit(PORTC,7);
	OCR1A=sleft;
	OCR1B=sright;
}

