/*
 * HOLD_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "HOLD_INT.h"

f32 Ttick = 0.004; //ms
u32 dis = 0;
u8 counter_t1_ov = 0;

void UltrasonicFunc(){
	static u8 edge = 0;

	//rising
	if (edge==0){
		/*TIMER1_setPreload(0);
		TIMER1_InitIcu(TIMER1_ICU_FALLING,2);//set prescaler 64
		edge=1;*/
		TIMER0_setPreload(0);
		TIMER0_start(TIMER0_DIV64);

		EXT_int0Int(EXT_FALLING);

		edge=1;

	}
	//falling
	else if (edge==1){
		/*u16 numTicks = TIMER1_getICR();
		f32 Time = numTicks * Ttick;
		dis = 17 * Time;
		TIMER1_InitIcu(TIMER1_ICU_RISING,2);//set prescaler 64
		edge = 0;*/
		u32 numTicks = TIMER0_getCounts();
		if(counter_t1_ov>=1){
			numTicks=numTicks+(counter_t1_ov*256);
		}
		f32 Time = numTicks * Ttick;
		dis = 17 * Time;

		LCD_sendNum(dis);
		LCD_clearDis();
		_delay_ms(1000);

		EXT_int0Int(EXT_RISING);

		edge = 0;
	}
}

void Timer0OvFunc(){
	counter_t1_ov++;
}

void HOLD_init(){

	//TR
	DIO_setPinDir(DIO_PINC6,DIO_OUTPUT);

	//ECHO
	DIO_setPinDir(DIO_PIND2,DIO_INPUT);

	//External Interrupt
	GI_enable();

	EXT_int0Int(EXT_RISING);

	EXT_setcallbackInt0(UltrasonicFunc);

	//Timer0
	TIMER0_initNormal();

	TIMER0_setCallbackOv(Timer0OvFunc);
}


void HOLD_Start(){
	DIO_setPinValue(DIO_PINC6,DIO_HIGH);
	_delay_us(11);
	DIO_setPinValue(DIO_PINC6,DIO_LOW);
	_delay_ms(100);
}
u32 HOLD_Retrun(){
	return dis;
}
