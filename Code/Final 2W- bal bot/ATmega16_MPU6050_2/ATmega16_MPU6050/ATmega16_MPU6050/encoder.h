/*
 * encoder.h
 *
 * Created: 18-08-2019 08:47:30
 *  Author: Owner
 */ 

#include <avr/io.h>
#ifndef ENCODER_H_
#define ENCODER_H_


 int Left_counter = 0; 
 int Left_State;
 int Left_LastState;  
int Right_counter = 0;
int Right_State;
int Right_LastState;


int count_step_left();
int count_step_right();
void gotostep(int count,char dir);

#endif /* ENCODER_H_ */