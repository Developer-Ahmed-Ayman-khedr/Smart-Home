/*
 * TIMER2_PROG.c
 *
 * Created: 8/16/2024 8:16:32 PM
 *  Author: DELL
 */


#include "TIMER2_INT.h"

void TIMER2_initNormal()
{
	//select normal mode
	CLEAR_BIT(TCCR2,WGM20);
	CLEAR_BIT(TCCR2,WGM21);

	//enable
	SET_BIT(TIMSK,TOIE2);
}

void TIMER2_initCTC()
{
	//select ctc mode
	CLEAR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);

	//enable
	SET_BIT(TIMSK,OCIE2);
}

void TIMER2_initFPWM()
{
	//select normal mode
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);

	//Set output mode
	#if (TIMER2_PWM_mode==TIMER2_NON_INVERTED)
	//Non inverting
	CLEAR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
	#elif (TIMER2_PWM_mode==TIMER2_INVERTED)
	//Inverting
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
	#endif

}

void TIMER2_init_Phase_Correct_PWM()
{
	//select normal mode
	SET_BIT(TCCR2,WGM20);
	CLEAR_BIT(TCCR2,WGM21);

	//Set output mode
	#if (TIMER0_PWM_mode==TIMER0_NON_INVERTED)
	//Non inverting
	CLEAR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
	#elif (TIMER0_PWM_mode==TIMER0_INVERTED)
	//Inverting
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
	#endif

}

void TIMER2_start(u8 prescaler)
{
	if(prescaler == TIMER2_DIV0)
	{
		SET_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV8)
	{
		CLEAR_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV32)
	{
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV64)
	{
		CLEAR_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV128)
	{
		SET_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV256)
	{
		CLEAR_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV1024)
	{
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}

	else if(prescaler == TIMER2_STOP)
	{
		CLEAR_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
}

void TIMER2_setPreload(u8 value){
	TCNT2 = value;
}

void TIMER2_setOCR(u8 value){
	OCR2 = value;
}

u8 TIMER2_getCounter(){
	return TCNT2;
}


//pointer to Overflow function
void (*TIMER2_OvFunc)();

//call back function to send the function from the main function
void TIMER2_setCallbackOv(void (*ptr)()){
	TIMER2_OvFunc = ptr;
}

//Vector Table Function that belongs to INT0
//number(in vector table) - 1
void __vector_5() __attribute__((signal));
void __vector_5(){
	TIMER2_OvFunc();
}

/*//pointer to CTC function
void (*TIMER2_CTCFunc)();

//call back function to send the function from the main function
void TIMER2_setcallbackCTC(void (*ptr)()){
	TIMER2_CTCFunc = ptr;
}

//Vector Table Function that belongs to INT0
//number(in vector table) - 1
void __vector_10() __attribute__((signal));
void __vector_10(){
	TIMER2_CTCFunc();
}*/
