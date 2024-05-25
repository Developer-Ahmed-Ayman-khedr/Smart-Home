/*
 * DOORCONTROL_PROG.c
 *
 *  Created on: May 25, 2024
 *      Author: ahmed
 */

#include "DOORCONTROL_INT.h"

void DOORCONTROL_init(){
	//Flag to make the function TIMER1_initFastPwmMod14() and TIMER1_setFrequency() get executed once
	u8 flag1=0;

	if(flag1==0){

		//Servo Motor control PIN
		DIO_setPinDir(DIO_PIND5,DIO_OUTPUT);

		TIMER1_initFastPwmMod14();

		TIMER1_setFrequency(50);

		flag1++;
	}
}

void DOORCONTROL_Start(u8* Ma_Fl_ptr){
	//Flag to make the function Timer1_InitICU() get executed once
	u8 flag2=0;
	//Open the door
	TIMER1_setOcr(499);

	//Wait for the Ultrasonic Sensor to return a distance greater than 30cm
	if(flag2==0){
		HOLD_init();
		flag2++;
	}

	HOLD_Start();

	if(HOLD_Retrun()>30){
		//Close the door
		TIMER1_initFastPwmMod14();

		TIMER1_setFrequency(50);

		TIMER1_setOcr(375);

		* Ma_Fl_ptr = 5 ;
	}
}
