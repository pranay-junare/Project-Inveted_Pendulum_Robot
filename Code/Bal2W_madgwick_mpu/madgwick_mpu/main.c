/*
 * mahony_filter.c
 *
 * Created: 09-08-2019 12.55.42 AM
 * Author : PRANAYJUNARE
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "mpu_init.h"
#include "init.h"
#include "pid.h"
#include "prep.h"
#include "I2C_Master_H_file.h"
#include "MPU6050_res_define.h"
#include "lcd.h"
#include "MadgwickAHRS.h"
#include "motor.h"

int main(void)
{

    init();
	lcd_init();
	lcd_clear();
	MPU6050_Init();
    /* Replace with your application code */
	// Gyro_off_calculation();              //run this to calculate offset
  
    while (1) 
    { 
		Read_RawValue();
	    MadgwickAHRSupdateIMU(Gyro_x_pro,Gyro_y_pro,Gyro_z_pro,Acc_x_pro,Acc_y_pro,Acc_z_pro); 
		 
	 //   pid_control();
			  
    }
}

