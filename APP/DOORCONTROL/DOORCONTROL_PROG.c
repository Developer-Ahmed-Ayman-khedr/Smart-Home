/*
 * DOORCONTROL_PROG.c
 *
 *  Created on: May 25, 2024
 *      Author: ahmed
 */

#include "DOORCONTROL_INT.h"

void DOORCONTROL_init(){

	//Servo Motor control PIN
	DIO_setPinDir(DIO_PIND5,DIO_OUTPUT);

	//Timer1
	TIMER1_initFastPwmMod14();

	TIMER1_setFrequency(50);
}

BOOL DOORCONTROL_Start(){
	//Open the door
	TIMER1_setOcr(499);

	//Start the Holding process
	HOLD_Start();

	//Wait for the Ultrasonic Sensor to return a distance greater than 30cm
	if(HOLD_Retrun()>30)
	{
		//Close the door
		TIMER1_setOcr(375);
		return TRUE;
	}
}
