/*
 * motor.h
 *
 * Created: 03-08-2019 5.56.22 PM
 *  Author: PRANAYJUNARE
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "prep.h"
//#include "init.h"

void forward(uint8_t sleft,uint8_t sright){
	sbit(PORTD,0);
	cbit(PORTD,1);
		sbit(PORTA,0);
		cbit(PORTA,1);
		//sbit(PORTC,7);
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

