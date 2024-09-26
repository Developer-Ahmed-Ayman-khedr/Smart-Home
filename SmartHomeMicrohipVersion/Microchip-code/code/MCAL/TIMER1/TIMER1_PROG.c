/*
 * TIMER1_PROG.c
 *
 * Created: 5/13/2024 9:02:55 PM
 *  Author: ahmed
 */

#include "TIMER1_INT.h" 

void TIMER1_initFastPwmMod14()
{
	//select mode 14(Fast PWM)
	CLEAR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	//select non inverting
	CLEAR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
}

void TIMER1_STOP(){
		CLEAR_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
}

void TIMER1_setOcr(u16 value)
{
	OCR1A = value;
}

void TIMER1_setFrequency(u16 pwm_frequency)
{
	//f = 50 Hz
	ICR1 = (16000000/(pwm_frequency*64))-1;
	//top = 4999
	//ICR1 = 4999;
	
	//select prescaller = 64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);
}

void TIMER1_InitIcu(u8 edge,u8 prescaller){
	//Set normal mode
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	CLEAR_BIT(TCCR1A,WGM12);
	CLEAR_BIT(TCCR1A,WGM13);
	
	//Edge detection
	if (edge==TIMER1_ICU_RISING)
	{
		SET_BIT(TCCR1B,ICES1);
	} 
	else if (edge==TIMER1_ICU_FALLING)
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
	
	//Enable
	SET_BIT(TIMSK,TICIE1);
	
	//Set prescaller
	if(prescaller == TIMER1_DIV0)
	{
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
	}
	else if(prescaller == TIMER1_DIV8)
	{
		CLEAR_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
	}
	else if(prescaller == TIMER1_DIV64)
	{
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
	}
	else if(prescaller == TIMER1_DIV256)
	{
		CLEAR_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
	}
	else if(prescaller == TIMER1_DIV1028)
	{
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
	}
}

void TIMER1_setPreload(u16 value){
	TCNT1 = value;
}

u16 TIMER1_getICR(){
	return ICR1;
}

//pointer to ICU function
void (*TIMER1_IcuFunc)();

//call back function to send the function from the main function
void TIMER1_setcallbackIcu(void (*ptr)()){
	TIMER1_IcuFunc = ptr;
}

//Vector Table Function that belongs to TIMER1
//number(in vector table) - 1
void __vector_6() __attribute__((signal));
void __vector_6(){
	TIMER1_IcuFunc();
}