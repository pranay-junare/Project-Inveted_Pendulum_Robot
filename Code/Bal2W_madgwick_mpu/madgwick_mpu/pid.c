/*
 * pid.c
 *
 * Created: 11-08-2019 8.17.31 PM
 *  Author: PRANAYJUNARE
 */ 


#include "pid.h"
#include "mpu_init.h"



////////////////////////Variables///////////////////////for pid
int Read = 0;
float angle = 0.0;
float elapsedTime, time, timePrev;        //Variables for time control
float angle_previous_error, angle_error;
int period = 50;  //Refresh rate period of the loop is 50ms
///////////////////////////////////////////////////////




///////////////////PID constants///////////////////////
float kp=50; //Mine was 260
float ki=0; //Mine was 0
float kd=250; //Mine was 40
float angle_setpoint = 0;           //Should be the distance from sensor to the middle of the bar in mm
float PID_p, PID_i, PID_d, PID_total;
///////////////////////////////////////////////////////




float mapping(float var, float in_low, float in_max, float out_low,float out_max){
	return (var-in_low)*(out_max-out_low)/(in_max-in_low) + out_low;
}



void pid_control()
{
	angle=pitch;
	if(angle>=(-0.3) && angle<=0.3){
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
		PID_total=mapping(PID_total,0,255,25,255);
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
		PID_total=mapping(PID_total,0,255,25,255);
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


