/*
 * serial.c
 *
 * Created: 07-03-2018 11:27:38 PM
 *  Author: Bhushan
 */ 
#include <avr/io.h>

#include "serial.h"


void serial_write(uint8_t data)
{
	loop_until_bit_is_set(UCSRA,UDRE);
	UDR = data;
}

uint8_t serial_read(void)
{
	loop_until_bit_is_set(UCSRA,RXC);
	return UDR;
}


uint8_t convertDecimalToBinary(int n)
{
	long long binaryNumber = 0;
	int remainder, i = 1, step = 1;
	while (n!=0)
	{
		remainder = n%2;
		/*printf("Step %d: %d/2, Remainder = %d, Quotient = %d\n", step++, n, remainder, n/2);*/
		n /= 2;
		binaryNumber += remainder*i;
		i *= 10;
	}
	return binaryNumber;
}