


#define F_CPU 8000000UL									/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>										/* Include AVR std. library file */
#include <util/delay.h>									/* Include delay header file */
#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>	
#include "lcd.h"
#include "motor.h"	
#include "prep.h"	
#include "init.h"							/* Include standard library file */
#include "MPU6050_res_define.h"							/* Include MPU6050 register define file */
#include "I2C_Master_H_file.h"							/* Include I2C Master header file */
#include "USART_RS232_H_file.h"						/* Include USART header file */

#include <math.h>

//////////////// mpu variable declarations/////////////////////
float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z,angxa=0,xtotal;
float gyrox_cal, gyroy_cal, gyroz_cal;
float time,fil_X;
char buffer[20], float_[10];
float Xa,Ya,Za,t;
float Xg=0,Yg=0,Zg=0, iXg=0,iYg=0,iZg=0,sum;
///////////////////////////////////////////////////////

////////////////////////Variables///////////////////////for pid
int Read = 0;
float angle = 0.0;
float elapsedTime, time, timePrev;        //Variables for time control
float angle_previous_error, angle_error;
int period = 50;  //Refresh rate period of the loop is 50ms
///////////////////////////////////////////////////////




///////////////////PID constants/////////////////////// 
float kp=510; //Mine was 260
float ki=0; //Mine was 0
float kd=250; //Mine was 40
float angle_setpoint = 0;           //Should be the distance from sensor to the middle of the bar in mm
float PID_p, PID_i, PID_d, PID_total;
///////////////////////////////////////////////////////



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
	Acc_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Temperature = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();
}



float get_angles()
{
		
		void get_values_mpu();
		{	for(int i=0;i<25;i++)
			{
				
				
				Read_RawValue();

				Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
				Ya = Acc_y/16384.0;
				Za = Acc_z/16384.0;
				
				Xg = (Gyro_x)*0.0048/131 ;
				Yg = Gyro_y/131;
				Zg = Gyro_z/131;


				angxa=asin(Ya/sqrt(Xa*Xa +Ya*Ya +Za*Za))*57.29;
				iXg=iXg+Xg;
				sum=sum+angxa;
			}
			sum=sum/25;
			
			
			lcd_gotoxy(1,1);
			lcd_string("angxg=");
			lcd_float(iXg);
			return sum;

		}

	
}

float mapping(float var, float in_low, float in_max, float out_low,float out_max){
	return (var-in_low)*(out_max-out_low)/(in_max-in_low) + out_low;
}



void pid_control()
{
		angle=fil_X;
		if(angle>=(-0.3) && angle<=0.3)
		{ 
			angle=0;
			forward(0,0);
		//	_delay_ms(10);
			}


					lcd_gotoxy(1,1);
					lcd_string("AngX=");
					lcd_float(angle);
		angle_error=angle_setpoint-angle;
		PID_p = kp *(- angle_error);
		float angle_difference = angle_error - angle_previous_error;
		PID_d = kd*((angle_error - angle_previous_error)/period);
		
		if(-1 < angle_error && angle_error < 1)
		PID_i = PID_i + (ki * angle_error);
		else
		PID_i = 0;
		
		
		PID_total = PID_p + PID_i + PID_d;



		PID_total= mapping(PID_total,-10000,10000,-255,255);
		
		if(PID_total>0)
		{
			PID_total=mapping(PID_total,0,255,30,255);
			if(PID_total>100)
			{
				PID_total+=70;
				//PID_total=mapping(PID_total,0,255,200,255);
				forward(PID_total,PID_total);
				lcd_gotoxy(2,1);
				lcd_string("F:");
				lcd_float(PID_total);
			}
			if(PID_total>255)
			{
				PID_total=255;
				//PID_total=mapping(PID_total,0,255,200,255);
				forward(PID_total,PID_total);
				lcd_gotoxy(2,1);
				lcd_string("F:");
				lcd_float(PID_total);
			}
// 						else if (PID_total>=25 && PID_total<=35){
// 							PID_total=0;
// 							
// 							forward(PID_total,PID_total);
// 					//	_delay_us(100);	
// 						lcd_gotoxy(2,1);
// 							lcd_string("FORWARD:");
// 						lcd_float(PID_total);
// 						//PID_total=0;
// 						}
					
			else{
			forward(PID_total,PID_total);
			lcd_gotoxy(2,1);
			lcd_string("F:");
			lcd_float(PID_total);}
			
		}
		if(PID_total<0)
		{
			PID_total=-PID_total;
			PID_total=mapping(PID_total,0,255,30,255);
			if(PID_total>100)
			{
				
				PID_total+=70;
				//PID_total=mapping(PID_total,0,255,200,255);
				backward(PID_total,PID_total);
				lcd_gotoxy(2,1);
				lcd_string("B:");
				lcd_float(PID_total);
			}
			if(PID_total>255)
			{
				PID_total=255;
				//PID_total=mapping(PID_total,0,255,200,255);
				backward(PID_total,PID_total);
				lcd_gotoxy(2,1);
				lcd_string("F:");
				lcd_float(PID_total);
			}
// 						else if (PID_total>=25 && PID_total<=35){
// 							PID_total=0;
// 							backward(PID_total,PID_total);
// 							//	_delay_us(100);
// 							lcd_gotoxy(2,1);
// 							lcd_string("FORWARD:");
// 						lcd_float(PID_total);
// 						
// 						}
					
			else{
			backward(PID_total,PID_total);
			lcd_gotoxy(2,1);
			lcd_string("B:");
			lcd_float(PID_total);
			}
				
		}
		angle_previous_error = angle_error;
		//angle_setpoint=0;
		//_delay_ms(1000);
	}



	
	void update_state(){
		TCNT0=0x00;
		
		Read_RawValue();

		Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
		Ya = Acc_y/16384.0;
		Za = Acc_z/16384.0;
		
		Xg = ((Gyro_x/131)+1.8673)*time ;          // calibrated
		//Xg = ((Gyro_x/131)-gyrox_cal)*time;
		Yg = Gyro_y/131;
		Zg = Gyro_z/131;
		
		
		
		angxa=asin(Ya/sqrt(Xa*Xa +Ya*Ya +Za*Za))*57.29;  //from accelerometer
		iXg=iXg+Xg;               //from gyro
		
		fil_X=0.988*iXg+0.012*angxa;
		 

		
		
		
		time=(float)TCNT0;
		time=time*(1.24/8000);
		
		
		//pid_control();
		
		
	}


	
	
int main()
{ 
	init();
	I2C_Init();	
						
	MPU6050_Init();										/* Initialize MPU6050 */
								/* Initialize USART with 9600 baud rate */
	lcd_init();		
	

	
	TCCR0 = (1<<CS02) | (1<<CS00); /* Timer0, normal mode, /1024 prescalar */
int count=0;
	while(1)
	
	     {   
			  update_state();
			  pid_control();
			 
               /* count++;
				//backward
				if(count<=800)
				{ angle_setpoint=0;
					  update_state();
			             pid_control();
				}
				else if(count>800 && count<=1200)      //forward
				{ angle_setpoint+=0.05;
					if(angle_setpoint>3)
					  angle_setpoint=3;
					update_state();
					pid_control();
				}
				else if(count>1200 && count<=1900)   //original
				 { angle_setpoint-=0.05;
					 if(angle_setpoint<-0.5)
					 angle_setpoint=-0.5;
					 update_state();
					 pid_control();
				 }
				 else
				  count=0;
				*/
				///front oscillation 
// 				else if(count>1600 && count<=2400)   
// 				 { angle_setpoint=0;
// 					 update_state();
// 					 pid_control();
// 				 }
// 				 else if(count>2400 && count<=2800)      //forward
// 				 { angle_setpoint-=0.05;
// 					 if(angle_setpoint>-3)
// 					 angle_setpoint=-3;
// 					 update_state();
// 					 pid_control();
// 				 }
// 				 else if(count>2800 && count<=3200)   //original
// 				 { angle_setpoint+=0.05;
// 					 if(angle_setpoint<0.5)
// 					 angle_setpoint=0;
// 					 update_state();
// 					 pid_control();
// 				 }
				
		 }
}


