/*
 * lcd.c
 *
 * Created: 07-03-2018 11:20:52 PM
 *  Author: Bhushan
 */ 

/*
 * lcd.c
 *
 * Created: 11-09-2015 12:29:23 PM
 *  Author: user
 */

/**
  ******************************************************************************
  * @file    lcd.c
  * @author  Robot Study Circle
  * @version V2.2
  * @date    8-sep-2015
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




#include "lcd.h"

/** @defgroup LCD Functions
* @{
*/

#if (LCD_MODE == PORTWISE)

/**
  * @brief  Used to send data latching pulse on EN
  * @param  None
  * @retval None
  */
void pulse(void)
{
	sbit(PORT(LCD_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(LCD_PORT),EN_BIT);				//Clear Enable Pin
	_delay_us(50);
}


/**
  * @brief  Used to write 8 bit data
  * @param  data: 8 bit data to be send
  * @retval None
  */
void lcd_write(uint8_t data)
{
	uint8_t temp;
	temp = data;
	temp = (temp & 0xF0);
	PORT(LCD_PORT) &= 0x0F;
	PORT(LCD_PORT) |= temp;
	sbit(PORT(LCD_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();

	data = data & 0x0F;
	data = data<<4;
	PORT(LCD_PORT) &= 0x0F;
	PORT(LCD_PORT) |= data;
	sbit(PORT(LCD_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();
}

/**
  * @brief  Used to write 8 bit command
  * @param  cmd: 8 bit command to be send
  * @retval None
  */
void lcd_cmd(uint8_t cmd)
{
	uint8_t temp;
	temp = cmd;
	temp = temp & 0xF0;
	PORT(LCD_PORT) &= 0x0F;
	PORT(LCD_PORT) |= temp;
	cbit(PORT(LCD_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();

	cmd = cmd & 0x0F;
	cmd = cmd<<4;
	PORT(LCD_PORT) &= 0x0F;
	PORT(LCD_PORT) |= cmd;
	cbit(PORT(LCD_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();

}

#endif

#if (LCD_MODE == BITWISE)
/**
  * @brief  Used to send data latching pulse on EN
  * @param  None
  * @retval None
  */
void pulse(void)
{
	sbit(PORT(EN_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);							//delay
	cbit(PORT(EN_PORT),EN_BIT);				//Clear Enable Pin
	_delay_us(50);
}


/**
  * @brief  Used to write 8 bit data
  * @param  data: 8 bit data to be send
  * @retval None
  */
void lcd_write(uint8_t data)
{

	COPY(data,7,PORT(D7_PORT),D7_BIT);
	COPY(data,6,PORT(D6_PORT),D6_BIT);
	COPY(data,5,PORT(D5_PORT),D5_BIT);
	COPY(data,4,PORT(D4_PORT),D4_BIT);
	sbit(PORT(RS_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();

	COPY(data,3,PORT(D7_PORT),D7_BIT);
	COPY(data,2,PORT(D6_PORT),D6_BIT);
	COPY(data,1,PORT(D5_PORT),D5_BIT);
	COPY(data,0,PORT(D4_PORT),D4_BIT);
	sbit(PORT(RS_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();
}

/**
  * @brief  Used to write 8 bit command
  * @param  cmd: 8 bit command to be send
  * @retval None
  */
void lcd_cmd(uint8_t cmd)
{
	COPY(cmd,7,PORT(D7_PORT),D7_BIT);
	COPY(cmd,6,PORT(D6_PORT),D6_BIT);
	COPY(cmd,5,PORT(D5_PORT),D5_BIT);
	COPY(cmd,4,PORT(D4_PORT),D4_BIT);
	cbit(PORT(RS_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();

	COPY(cmd,3,PORT(D7_PORT),D7_BIT);
	COPY(cmd,2,PORT(D6_PORT),D6_BIT);
	COPY(cmd,1,PORT(D5_PORT),D5_BIT);
	COPY(cmd,0,PORT(D4_PORT),D4_BIT);
	cbit(PORT(RS_PORT),RS_BIT);
	//cbit(lcd_port,RW);
	pulse();

}

#endif

/**
  * @brief  Used to set Cursor at Home Position
  * @param  None
  * @retval None
  */
void lcd_home(void)
{
	lcd_cmd(0x80);
	_delay_ms(3);
}

/**
  * @brief  Used to clear LCD and set cursor at home position
  * @param  None
  * @retval None
  */
void lcd_clear(void)
{
	lcd_cmd(0x01);
	_delay_ms(3);
}

/**
  * @brief  Used to set cursor at LCD. Index from 1
  * @param  row: row of cursor
  * @param column: column of cursor
  * @retval None
  */
void lcd_gotoxy(uint8_t row, uint8_t column)
{
	switch (row) {
	case 1:
		lcd_cmd(0x80 + column - 1); break;
	case 2:
		lcd_cmd(0xc0 + column - 1); break;
	case 3:
		lcd_cmd(0x90 + column - 1); break;
	case 4:
		lcd_cmd(0xd0 + column - 1); break;
	default:
		LCD_HOME;
	}
}

/**
  * @brief  Used to print String on LCD at current cursor position
  * @param  string: String to print
  * @retval None
  */
void lcd_string(char string[])
{
	while(*(string)!= '\0')
	{
		lcd_write(*(string++));
	}
}


/**
  * @brief  Used to print character on LCD at current cursor position
  * @param  character: ASCII character to print
  * @retval None
  */
void lcd_char(char character)
{
	lcd_write((uint8_t)character);
}

/**
  * @brief  Used to print Signed Decimal Integer on LCD at current cursor position
  * @param  integer: Signed integer to be printed
  * @retval None
  */
void lcd_int(int integer)
{
	char buffer[9];
	sprintf(buffer,"%d",integer);
	lcd_string(buffer);

}

/**
  * @brief  Used to print Unsigned Decimal Integer on LCD at current cursor position
  * @param  integer: unsigned integer to be printed
  * @retval None
  */
void lcd_uint(unsigned int integer)
{
	char buffer[9];
	sprintf(buffer,"%u",integer);
	lcd_string(buffer);

}
/**
  * @brief  Used to print Decimal Long Integer on LCD at current cursor position
  * @param  long_int: signed long integer to be printed
  * @retval None
  */
void lcd_long(long long_int)
{
	char buffer[8];
	sprintf(buffer, "%ld", long_int);
	lcd_string(buffer);
}

/**
  * @brief  Used to print floating point number on LCD at current cursor position with default Precision
  * @param  number: floating point number to be printed
  * @retval None
  */
void lcd_float(float number)
{
	char buffer[8];
	long above_deci = (long) number;
	number = (float) (number - above_deci);
	long below_deci = (long) (number*100);
	if(below_deci<0)
	{ 
	below_deci=-below_deci;		
	}
	sprintf(buffer,"%ld.%ld",above_deci,below_deci);
	lcd_string(buffer);
}

/**
  * @brief  Used to print floating point number on LCD at current cursor position with given precision
  * @param  number: floating point number to be printed
  * @param  digits: no. of digits to be printed before decimal point
  * @param  precision: no. of digits after decimal point
  * @retval None
  */
void lcd_float_print(float number, uint8_t digits, uint8_t precision)
{
	char buffer[12],buff_buffer[7];
	long above_deci = (long) number;
	number = (float) (number - above_deci);
	long below_deci = (long) ((number)*(pow(10,precision)));
	if(below_deci<0)
	{
		below_deci=-below_deci;
	}
	sprintf(buff_buffer,"%%0%uld",digits);
	sprintf(buffer,buff_buffer,above_deci);
	lcd_string(buffer);
	lcd_char('.');
	sprintf(buff_buffer,"%%%uld",precision);
	sprintf(buffer,buff_buffer,below_deci);
	lcd_string(buffer);
}


/**
  * @brief  Used to print integer on LCD at given cursor postion
  * @param  row: row of cursor
  * @param  column: column of cursor
  * @param  value: Integer to be printed
  * @param  digits: No. of digits to be displayed
  * @retval None
  */
void lcd_print(uint8_t row, uint8_t column, int32_t value, uint8_t digits)
{
	char buffer[8],buffer_of_buffer[5];

	lcd_gotoxy(row,column);
	sprintf(buffer_of_buffer,"%%0%ud",digits);
	sprintf(buffer,buffer_of_buffer,value);
	lcd_string(buffer);
}

/**
  * @brief  Used to print n bit register on LCD at current cursor position. Max 8 bit for BIN
  * @param  reg: n bit integer (max 32 bit)
  * @param  bits: No. of bits of integer
  * @param  base: Base of system (BIN, DEC, HEX)
  * @retval None
  */
void lcd_reg(uint32_t reg,uint8_t bits, uint8_t base)
{
	char buffer[12],buff_buffer[7];
	switch(base)
	{
		case BIN:
			reg = reg & 0x000000FF;
			sprintf(buffer,BYTETOBINARYPATTERN,BYTETOBINARY(reg));
			break;

		case HEX:
			sprintf(buff_buffer,"%%#%03ux",(bits/4)+2);
			sprintf(buffer,buff_buffer,reg);
			break;

		case DEC:
		default:
			if(bits == 8) bits = 3;
			else if(bits == 16) bits = 5;
			else if(bits == 32) bits = 10;
			else bits = 0;
			sprintf(buff_buffer,"%%%03uu",bits);
			sprintf(buffer,buff_buffer,reg);
			break;
	}
	lcd_string(buffer);
}

#if (LCD_MODE == PORTWISE)
/**
  * @brief  Used internally to Initialise LCD in 4 bit mode (Don't use directly)
  * @param  Nome
  * @retval None
  */
void lcd_set_4bit(void)
{
	_delay_ms(50);

	cbit(PORT(LCD_PORT),RS_BIT);				//RS=0 --- Command Input
	//cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	PORT(LCD_PORT) = 0x30;				//Sending 3 in the upper nibble
	sbit(PORT(LCD_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(LCD_PORT),EN_BIT);				//Clear Enable Pin

	_delay_ms(5);

	cbit(PORT(LCD_PORT),RS_BIT);				//RS=0 --- Command Input
	//cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	PORT(LCD_PORT) = 0x30;				//Sending 3 in the upper nibble
	sbit(PORT(LCD_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(LCD_PORT),EN_BIT);				//Clear Enable Pin

	_delay_ms(5);

	cbit(PORT(LCD_PORT),RS_BIT);				//RS=0 --- Command Input
	//cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	PORT(LCD_PORT) = 0x30;				//Sending 3 in the upper nibble
	sbit(PORT(LCD_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(LCD_PORT),EN_BIT);				//Clear Enable Pin

	_delay_ms(5);

	cbit(PORT(LCD_PORT),RS_BIT);				//RS=0 --- Command Input
	//	cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	PORT(LCD_PORT) = 0x20;				//Sending 2 in the upper nibble to initialize LCD 4-bit mode
	sbit(PORT(LCD_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(LCD_PORT),EN_BIT);				//Clear Enable Pin
	_delay_ms(5);
}
#endif

#if (LCD_MODE == BITWISE)
/**
  * @brief  Used internally to Initialise LCD in 4 bit mode (Don't use directly)
  * @param  Nome
  * @retval None
  */
void lcd_set_4bit(void)
{
	uint8_t data;
	_delay_ms(50);

	cbit(PORT(RS_PORT),RS_BIT);				//RS=0 --- Command Input
	//cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	data = 0x30;				//Sending 3 in the upper nibble

	COPY(data,7,PORT(D7_PORT),D7_BIT);
	COPY(data,6,PORT(D6_PORT),D6_BIT);
	COPY(data,5,PORT(D5_PORT),D5_BIT);
	COPY(data,4,PORT(D4_PORT),D4_BIT);

	sbit(PORT(EN_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(EN_PORT),EN_BIT);				//Clear Enable Pin

	_delay_ms(5);

	cbit(PORT(RS_PORT),RS_BIT);				//RS=0 --- Command Input
	//cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	data = 0x30;				//Sending 3 in the upper nibble

	COPY(data,7,PORT(D7_PORT),D7_BIT);
	COPY(data,6,PORT(D6_PORT),D6_BIT);
	COPY(data,5,PORT(D5_PORT),D5_BIT);
	COPY(data,4,PORT(D4_PORT),D4_BIT);

	sbit(PORT(EN_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(EN_PORT),EN_BIT);				//Clear Enable Pin

	_delay_ms(5);

	cbit(PORT(RS_PORT),RS_BIT);				//RS=0 --- Command Input
	//cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	data = 0x30;				//Sending 3 in the upper nibble

	COPY(data,7,PORT(D7_PORT),D7_BIT);
	COPY(data,6,PORT(D6_PORT),D6_BIT);
	COPY(data,5,PORT(D5_PORT),D5_BIT);
	COPY(data,4,PORT(D4_PORT),D4_BIT);

	sbit(PORT(EN_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(EN_PORT),EN_BIT);				//Clear Enable Pin

	_delay_ms(5);

	cbit(PORT(RS_PORT),RS_BIT);				//RS=0 --- Command Input
	//	cbit(lcd_port,RW);				//RW=0 --- Writing to LCD
	data = 0x20;				//Sending 2 in the upper nibble to initialize LCD 4-bit mode
	COPY(data,7,PORT(D7_PORT),D7_BIT);
	COPY(data,6,PORT(D6_PORT),D6_BIT);
	COPY(data,5,PORT(D5_PORT),D5_BIT);
	COPY(data,4,PORT(D4_PORT),D4_BIT);

	sbit(PORT(EN_PORT),EN_BIT);				//Set Enable Pin
	_delay_us(1);					//delay
	cbit(PORT(EN_PORT),EN_BIT);				//Clear Enable Pin
	_delay_ms(5);
}
#endif

/**
  * @brief  Used to Initialise LCD
  * @param  Nome
  * @retval None
  */
void lcd_init(void)
{
	//lcd port init
	#if (LCD_MODE == PORTWISE)
	sbit(DDR(LCD_PORT),RS_BIT);
	sbit(DDR(LCD_PORT),EN_BIT);
	DDR(LCD_PORT) |= 0xF0;
	#endif

	#if (LCD_MODE == BITWISE)
	sbit(DDR(RS_PORT),RS_BIT);
	sbit(DDR(EN_PORT),EN_BIT);
	sbit(DDR(D4_PORT),D4_BIT);
	sbit(DDR(D5_PORT),D5_BIT);
	sbit(DDR(D6_PORT),D6_BIT);
	sbit(DDR(D7_PORT),D7_BIT);
	#endif

	lcd_set_4bit();

	lcd_cmd(0x28); //4-bit mode and 5x8 dot character font
	_delay_ms(5);
	//lcd_cmd(0x0F); //Turn on LCD and cursor + blinking
	lcd_cmd(0x0E);//Turn on LCD and cursor + no blinking
	_delay_ms(5);
	lcd_cmd(0x01); //Clear LCD display
	_delay_ms(5);
	lcd_cmd(0x06); //Auto increment cursor position
	_delay_ms(5);
	lcd_cmd(0x80); //Set cursor position
	_delay_ms(5);

}
/**
  * @brief  Used to print string in center of LCD at given row
  * @param  row: row to which print
    @param  string: string to print
  * @retval None
  */
void lcd_center(int row, char string[])
{
	int len = strlen(string);
	//lcd_gotoxy(row, 7 - len/2);			//for 20x4 lcd
	lcd_gotoxy(row, 8 - len/2);			//for 16X2 or 16x4 LCD
	lcd_string(string);
}
