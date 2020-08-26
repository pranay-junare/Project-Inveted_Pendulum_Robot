/*
 * prep.h
 *
 * Created: 07-03-2018 11:32:13 PM
 *  Author: Bhushan
 */ 


#ifndef PREP_H_
#define PREP_H_

#include "avr\sfr_defs.h"
#include "stdint.h"

#define sbit(sfr,bit)		(sfr |= (1<<bit))
#define cbit(sfr,bit)		(sfr &= ~(1<<bit))
#define check(sfr, bit)		((sfr & ( 1<<bit ) ) ? (uint8_t)1 : (uint8_t)0)
#define COPY(src_sfr,src_bit,dest_sfr,dest_bit) ((check(src_sfr,src_bit)? sbit(dest_sfr,dest_bit) : cbit(dest_sfr,dest_bit)))

#define _CONCAT(arg1, arg2) arg1##arg2
#define PORT(reg) _CONCAT(PORT,reg)
#define DDR(reg) _CONCAT(DDR,reg)
#define PIN(reg) _CONCAT(PIN,reg)

#define DEC (10)
#define BIN (2)
#define HEX (16)
#define OCT (8)

#define upper_byte16(reg16) ((reg16>>8)&0x00ff)
#define lower_byte16(reg16) (reg16&0x00ff)

#define upper_byte32(reg32) ((reg32>>24)&0x00ff)
#define mid_upper_byte32(reg32) ((reg32>>16)&0x00ff)
#define mid_lower_byte32(reg32) ((reg32>>8)&0x00ff)
#define lower_byte32(reg32) (reg32&0x00ff)

#define upper_word32(reg32) ((reg32>>16)&0x0000ffff)
#define lower_word32(reg32) (reg32&0x0000ffff)




#endif /* PREP_H_ */