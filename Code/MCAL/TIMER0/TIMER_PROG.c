/*
 * TIMER_PROG.c
 *
 * Created: 5/1/2024 7:35:33 PM
 *  Author: ahmed
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TIMRE0_INT.h"

void TIMER0_initNormal()
{
	//select normal mode
	CLEAR_BIT(TCCR0,WGM00);
	CLEAR_BIT(TCCR0,WGM01);
	
	//enable
	SET_BIT(TIMSK,TOIE0);
}

void TIMER0_start(u8 prescaler)
{
	if(prescaler == TIMER0_RISING)
	{
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_FALING)
	{
		CLEAR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV0)
	{
		SET_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV8)
	{
		CLEAR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV64)
	{
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV256)
	{
		CLEAR_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	
}

void TIMER0_setPreload(u8 value){
	TCNT0 = value;
}

u8 TIMER0_getCounter(){
	return TCNT0;
}

void (*TIMER0_OvFunc)();

//call back function to send the function from the main function
void TIMER_setcallbackOv(void (*ptr)()){
	TIMER0_OvFunc = ptr;
}

//Vector Table Function that belongs to INT0
//number(in vector table) - 1
void __vector_11() __attribute__((signal));
void __vector_11(){
	TIMER0_OvFunc();
	//LCD_Shift(LCD_SHIFT_DIS_LIFT);
}
