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
	GI_enable();

	TIMER1_initFastPwmMod14();

	TIMER1_setFrequency(50);

}

void DOORCONTROL_Start(u8* Ma_Fl_ptr){

	//Open the door
	TIMER1_setOcr(499);

	_delay_ms(1000);
	//Close the door
	TIMER1_setOcr(375);

	_delay_ms(1000);
	//Wait for the Ultrasonic Sensor to return a distance greater than 30cm
	//HOLD_Start();
	//LCD_sendNum(HOLD_Retrun());

	//if(HOLD_Retrun()>30)
	{


		//* Ma_Fl_ptr = 5 ;
	}
}
