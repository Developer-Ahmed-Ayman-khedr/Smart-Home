/*
 * HOLD_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "HOLD_INT.h"

f32 Ttick = 0.004, TONTime=0; //ms
u32 dis = 0;
u32 OnCounter = 0, OvCounter=0,TimeOn=0;
u8 state = 0;

void Timer0OvFunc(){
	OvCounter++;
}

void UltrasonicFunc(){
	//rising
	if (state==0){
		/*TIMER1_setPreload(0);
		TIMER1_InitIcu(TIMER1_ICU_FALLING,2);//set prescaler 64
		edge=1;*/
		TIMER0_setPreload(0);

		OvCounter = 0;

		EXT_int0Int(EXT_FALLING);

		state++;

	}
	//falling
	else if (state==1){
		/*u16 numTicks = TIMER1_getICR();
		f32 Time = numTicks * Ttick;
		dis = 17 * Time;
		TIMER1_InitIcu(TIMER1_ICU_RISING,2);//set prescaler 64
		edge = 0;*/
		TimeOn = TIMER0_getCounts();

		OnCounter = OvCounter;

		EXT_int0Int(EXT_RISING);

		state++;
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
	//Start the timer
	TIMER0_start(TIMER0_DIV64);

	DIO_setPinValue(DIO_PINC6,DIO_HIGH);
	_delay_us(11);
	DIO_setPinValue(DIO_PINC6,DIO_LOW);
	_delay_ms(100);
	if(state==2){
		TONTime = Ttick*(TimeOn+(256*OnCounter));
		dis = 17 * TONTime;

		LCD_sendFloatNum(TONTime);
		LCD_sendNum(dis);
		LCD_clearDis();
		_delay_ms(1000);
		state = 0;
	}

}
u32 HOLD_Retrun(){
	return dis;
}
