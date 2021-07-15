/*
 * pid.h
 *
 * Created: 11-08-2019 8.17.14 PM
 *  Author: PRANAYJUNARE
 */ 


#ifndef PID_H_
#define PID_H_


////////////////////////Variables///////////////////////for pid
extern int Read;
extern float angle;
extern float elapsedTime, time, timePrev;        //Variables for time control
extern float angle_previous_error, angle_error;
extern int period;  //Refresh rate period of the loop is 50ms
///////////////////////////////////////////////////////




///////////////////PID constants///////////////////////
extern float kp; //Mine was 20
extern float ki; //Mine was 0.25
extern float kd; //Mine was 1500
extern float angle_setpoint;           //Should be the distance from sensor to the middle of the bar in mm
extern float PID_p, PID_i, PID_d, PID_total;
///////////////////////////////////////////////////////



void pid_control();
float mapping(float var, float in_low, float in_max, float out_low,float out_max);

#endif /* PID_H_ */