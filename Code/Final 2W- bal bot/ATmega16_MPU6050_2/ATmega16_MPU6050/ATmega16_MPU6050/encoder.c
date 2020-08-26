/*
 * encoder.c
 *
 * Created: 18-08-2019 09:10:32
 *  Author: Owner
 */ 

#include <avr/io.h>
#include "encoder.h"
#include "prep.h"
//#include "motor.h"


int count_step_left(){
	Left_State=check(PINC,2);
	
	 if (Left_State != Left_LastState){
		 // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
		 if (check(PINC,2) != Left_State) {
			 Left_counter ++;
			 } else {
			 Left_counter --;
		 }

	 }
	 Left_LastState =Left_State;
	 return Left_counter;
}

int count_step_right(){
	Right_State=check(PINC,3);
	
	if (Right_State != Right_LastState){
		// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
		if (check(PINC,2) != Right_State) {
			Right_counter ++;
			} else {
			Right_counter --;
		}

	}
	Right_LastState =Right_State;
	return Right_counter;
}

void gotostep(int count,char dir){

while(Left_counter!=count){
	if(dir == 'F'){
	Left_State=check(PINC,2);
	
	if (Left_State != Left_LastState){
		// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
		if (check(PINC,2) != Left_State) {
			Left_counter ++;
			forward(190,190);
			} else {
			Left_counter --;
		}

	}
	Left_LastState =Left_State;
	}
	if(dir == 'B'){
		Left_State=check(PINC,2);
		
		if (Left_State != Left_LastState){
			// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
			if (check(PINC,2) != Left_State) {
				Left_counter ++;
				backward(190,190);
				} else {
				Left_counter --;
			}

		}
		Left_LastState =Left_State;
	}
	}
}