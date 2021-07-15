/*
 * mpu_init.c
 *
 * Created: 09-08-2019 5.07.59 PM
 *  Author: PRANAYJUNARE
 */ 

#include "mpu_init.h"


void MPU6050_Init()										/* Gyro initialization function */
{
	_delay_ms(150);										/* Power up time >100ms */
	I2C_Start_Wait(0xD0);								/* Start with device write address */
	I2C_Write(SMPLRT_DIV);								/* Write to sample rate register */
	I2C_Write(0x07);									/* 1KHz sample rate */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_1);								/* Write to power management register */
	I2C_Write(0x01);									/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG);									/* Write to Configuration register */
	I2C_Write(0x00);									/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);								/* Write to Gyro configuration register */
	I2C_Write(0x00);									/* Full scale range +/- 250 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);								/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();
}

void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);								/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);							/* Write start location address from where to read */
	I2C_Repeated_Start(0xD1);							/* I2C start with device read address */
}


void Read_RawValue()
{
	MPU_Start_Loc();									/* Read Gyro values */
	Acc_x_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_y_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_z_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Temperature_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_x_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_y_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_z_raw = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();
	
	Acc_x_pro =(float) Acc_x_raw/16384.0;
	Acc_y_pro = (float)Acc_y_raw/16384.0;
	Acc_z_pro =(float) Acc_z_raw/16384.0;
	
	Gyro_x_pro = (float)Gyro_x_raw*0.01745392/131 ;       //converted into radians 
	Gyro_y_pro = (float)Gyro_y_raw*0.01745392/131;
	Gyro_z_pro =(float) Gyro_z_raw*0.01745392/131;
	
	Gyro_x_pro+=0.0337758;          //offsets value are cleared
	Gyro_y_pro-=0.0240322;
	Gyro_z_pro-=0.0160796;
}

 
 void Gyro_off_calculation()
   {
   	 for(int i=0;i<10000;i++)
  	   {  Read_RawValue();
		  Gyro_x_off+=Gyro_x_pro;
		  Gyro_y_off+=Gyro_y_pro;
		  Gyro_z_off+=Gyro_z_pro;
		}
// 		Gyro_x_off/=10000;
// 		Gyro_y_off/=10000;                                 //uncomment one by one as necessary as lcd doesn't print up to that accuraucy
// 		Gyro_z_off/=10000;

// 		 lcd_gotoxy(1,1);
// 		 lcd_string("X:");
// 		 lcd_float_print(Gyro_x_off,4,4);
		 
		  lcd_gotoxy(2,1);
		  lcd_string("Y:");
		  lcd_float_print(Gyro_y_off,4,4);
		  
		   lcd_gotoxy(1,1);
		   lcd_string("Z:");
		   lcd_float_print(Gyro_z_off,4,4);
		   
		   
		   //remember to divide by 10000(rad)
   }