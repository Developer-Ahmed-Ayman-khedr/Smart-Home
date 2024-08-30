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

	//Close the door
	TIMER1_setOcr(374);

}

void DOORCONTROL_Start(){
	u8 UartSend;
	//Start the Holding process
	HOLD_Start();

	UART_sendData(UartSend);

	if(HOLD_Retrun()<30)
	{
		//Open the door
		TIMER1_setOcr(499);
	}

	//Wait for the Ultrasonic Sensor to return a distance greater than 30cm

	while(HOLD_Retrun()<=30){
		HOLD_Start();
		UartSend = (u8)HOLD_Retrun();
	}
	if (HOLD_Retrun()>30)
	{
		//Close the door
		TIMER1_setOcr(374);
	}
}
