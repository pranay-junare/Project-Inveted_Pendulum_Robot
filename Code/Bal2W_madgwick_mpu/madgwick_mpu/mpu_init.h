/*
 * mpu_init.h
 *
 * Created: 09-08-2019 5.08.44 PM
 *  Author: PRANAYJUNARE
 */ 


#ifndef MPU_INIT_H_
#define MPU_INIT_H_

#include "MPU6050_res_define.h"							/* Include MPU6050 register define file */
#include "I2C_Master_H_file.h"							/* Include I2C Master header file */
#include "MPU6050_res_define.h"


int16_t Acc_x_raw,Acc_y_raw,Acc_z_raw,Temperature_raw,Gyro_x_raw,Gyro_y_raw,Gyro_z_raw;
float Acc_x_pro,Acc_y_pro,Acc_z_pro,Temperature_pro,Gyro_x_pro,Gyro_y_pro,Gyro_z_pro;
float Gyro_x_off,Gyro_y_off,Gyro_z_off;
float yaw,pitch,roll;
float qw,qx,qy,qz;
float a;

void MPU6050_Init();
void MPU_Start_Loc();
void Read_RawValue();
void Gyro_off_calculation();


#endif /* MPU_INIT_H_ */