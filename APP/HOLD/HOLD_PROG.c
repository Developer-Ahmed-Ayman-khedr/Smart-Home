/*
 * HOLD_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "HOLD_INT.h"

u8 vhold;

void HOLD_UltrasonicFunc(){
	static f32 Ttick = 0.004; //ms
	static u32 dis = 0;
	static u8 edge = 0;
	//rising
	if (edge==0){
		TIMER1_setPreload(0);
		TIMER1_InitIcu(TIMER1_ICU_FALLING,2);//set prescaler 64
		edge=1;
	}
	//falling
	else if (edge==1){
		u16 numTicks = TIMER1_getICR();
		f32 Time = numTicks * Ttick;
		dis = 17 * Time;
		TIMER1_InitIcu(TIMER1_ICU_RISING,2);//set prescaler 64
		edge = 0;
	}

	if (dis<=30) {
		vhold = 2;
	}
}


void HOLD_init(){
	GI_enable();

	TIMER1_InitIcu(TIMER1_ICU_RISING,2);//set prescaler 64

	TIMER1_setcallbackIcu(HOLD_UltrasonicFunc);
}


void HOLD_Start(u8* Ma_Fl_ptr){
	DIO_setPinValue(DIO_PIND1,DIO_HIGH);
	_delay_us(10);
	DIO_setPinValue(DIO_PIND1,DIO_LOW);
	_delay_ms(100);

	if (vhold==2) {
		*Ma_Fl_ptr = 2;
	}
}