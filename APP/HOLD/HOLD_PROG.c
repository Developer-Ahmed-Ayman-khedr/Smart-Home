/*
 * HOLD_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "HOLD_INT.h"

f32 Ttick = 0.004, TONTime=0; //ms
u32 dis;
u32 OvCounter=0, TimeOn=0;
u8 edge = 0;

void Timer0OvFunc(){
	OvCounter++;
}

void UltrasonicFunc(){
	//rising
	if (edge==0){

		TIMER0_setPreload(0);
		TIMER0_start(TIMER0_DIV64);

		OvCounter = 0;

		EXT_int0Int(EXT_FALLING);

		edge++;

	}
	//falling
	else if (edge==1){
		TIMER0_start(TIMER0_STOP);
		TimeOn = TIMER0_getCounts();

		TONTime = Ttick*(TimeOn+(256*OvCounter));
		dis = 17 * TONTime;

		EXT_int0Int(EXT_RISING);

		edge = 0;
	}
}

void HOLD_init(){

	//TR
	DIO_setPinDir(DIO_PINC6,DIO_OUTPUT);

	//ECHO
	DIO_setPinDir(DIO_PIND2,DIO_INPUT);

	//Timer0
	TIMER0_initNormal();

	TIMER0_setCallbackOv(Timer0OvFunc);



	//External Interrupt
	EXT_int0Int(EXT_RISING);

	EXT_setcallbackInt0(UltrasonicFunc);
}

void HOLD_Start(){
	DIO_setPinValue(DIO_PINC6,DIO_HIGH);
	_delay_us(11);
	DIO_setPinValue(DIO_PINC6,DIO_LOW);
}
u32 HOLD_Retrun(){
	return dis;
}
