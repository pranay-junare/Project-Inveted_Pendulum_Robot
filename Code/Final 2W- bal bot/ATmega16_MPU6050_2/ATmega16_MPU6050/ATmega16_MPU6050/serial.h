/*
 * serial.h
 *
 * Created: 07-03-2018 11:27:49 PM
 *  Author: Bhushan
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#define SERIAL_DDR DDRD
#define RX_BIT PD0
#define TX_BIT PD1

void serial_write(uint8_t data);
uint8_t serial_read(void);
uint8_t convertDecimalToBinary(int n);



#endif /* SERIAL_H_ */