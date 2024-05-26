/*
 * TIMER0_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: DELL
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER0_INT.h"

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
	if(prescaler == TIMER0_DIV0)
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
	else if(prescaler == TIMER0_DIV1028)
	{
		SET_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_EXT_RISING)
	{
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}

}


void TIMER0_setPreload(u8 value)
{
	TCNT0 = value;
}

u8 TIMER0_getCounts()
{
	return TCNT0;
}

void (*TIMER0_ovFunc)();

void TIMER0_setCallbackOv(void (*func)())
{
	TIMER0_ovFunc = func;
}

//num(in vector table)-1
void __vector_11() __attribute__((signal));
void __vector_11()
{
	TIMER0_ovFunc();
}



void TIMER0_initCtc()
{
	//select normal mode
	CLEAR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	//enable
	SET_BIT(TIMSK,OCIE0);
}

void TIMER0_setOcr(u8 value)
{
	OCR0 = value;
}

void (*TIMER0_ctcFunc)();

void TIMER0_setCallbackCtc(void (*func)())
{
	TIMER0_ctcFunc = func;
}

//num(in vector table)-1
void __vector_10() __attribute__((signal));
void __vector_10()
{
	TIMER0_ctcFunc();
}



void TIMER0_initFastPwm()
{
	//select normal mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	#if(TIMER0_PWM_MODE == TIMER0_NON_INVERTED)
	//non inverting
	CLEAR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	#elif(TIMER0_PWM_MODE == TIMER0_INVERTED)
	//inverting
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	#endif

}
