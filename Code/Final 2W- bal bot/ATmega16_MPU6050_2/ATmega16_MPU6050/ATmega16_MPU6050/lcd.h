/*
 * lcd.h
 *
 * Created: 07-03-2018 11:20:43 PM
 *  Author: Bhushan
 */ 


#ifndef LCD_H_
#define LCD_H_

/********************************************************************************
  * @file    lcd.h
  * @author  Robot Study Circle
  * @version V2.2
  * @date    5-Aug-2015
  * @brief   LCD Driver for AVR
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of LCD :
  *           + Initialization of LCD (4 bit mode)
  *			  + Bitwise and Portwise Mapping of Pins
  *           + Printing operation functions
  *			  + Cursor Operations
  *
  */

/* Private define ------------------------------------------------------------*/
#define F_CPU 8000000L

#define PORTWISE 0
#define BITWISE 1

#ifndef F_CPU
	#error "F_CPU not defined for lcd.h"
#endif


/* Includes ------------------------------------------------------------------*/
#include "avr/sfr_defs.h"
#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "string.h"
#include "prep.h"
/************************************************************************/
/*					 USER Defines
   LCD Controlling Mode : Port wise or Bitwise                     */
/************************************************************************/
#define  LCD_MODE BITWISE

#if (LCD_MODE == PORTWISE)
#define RS_BIT 2
#define RW_BIT 1
#define EN_BIT 3
#define LCD_PORT C
#endif

#if (LCD_MODE == BITWISE)
#define RS_PORT B
#define RS_BIT 1

#define EN_PORT B
#define EN_BIT 2

#define D4_PORT B
#define D4_BIT 3

#define D5_PORT B
#define D5_BIT 4

#define D6_PORT D
#define D6_BIT 6

#define D7_PORT B
#define D7_BIT 0

#endif

/************************************************************************/

#if((LCD_MODE != PORTWISE) && (LCD_MODE != BITWISE))
	#error "LCD_MODE is incorrect"
#endif

#ifndef LCD_MODE
	#error "LCD_MODE not defined"
#endif


/* Private defines */
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
(byte & 0x80 ? 1 : 0), \
(byte & 0x40 ? 1 : 0), \
(byte & 0x20 ? 1 : 0), \
(byte & 0x10 ? 1 : 0), \
(byte & 0x08 ? 1 : 0), \
(byte & 0x04 ? 1 : 0), \
(byte & 0x02 ? 1 : 0), \
(byte & 0x01 ? 1 : 0)

/**
  * @brief  Clears the LCD and set cursor to Home Position
  * @param  None
  * @retval None
  */

#define CLEAR_LCD lcd_clear();

/**
  * @brief  Sets cursor to Home Position
  * @param  None
  * @retval None
  */
#define LCD_HOME lcd_home();


/* User define ------------------------------------------------------------*/

/** @defgroup LCD Operating Mode Definitions
  * @brief    In PORTWISE Mode Px4 to Px7 of Port must be mapped to D4 to D7 of LCD. In BITWISE mode all signals can be mapped to any ports.
  * @{
  */


/* Function Declarations */
void pulse(void);
void lcd_write(uint8_t data);
void lcd_cmd(uint8_t cmd);
void lcd_home(void);
void lcd_clear(void);
void lcd_gotoxy(uint8_t row, uint8_t column);
void lcd_string(char string[]);
void lcd_char(char character);
void lcd_int(int integer);
void lcd_uint(unsigned int integer);
void lcd_long(long long_int);
void lcd_float(float number);
void lcd_float_print(float number, uint8_t digits, uint8_t precision);
void lcd_print(uint8_t row, uint8_t column, int32_t value, uint8_t digits);
void lcd_reg(uint32_t reg,uint8_t bits, uint8_t base);
void lcd_set_4bit(void);
void lcd_init(void);
void lcd_center(int row, char string[]);

#endif /* LCD_H_ */