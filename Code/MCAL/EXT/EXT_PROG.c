/*
 * EXT_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: ahmed
 */


#include "EXT_INT.h"

void EXT_int0Int(u8 Logic){
	if (Logic==EXT_RISING)
	{
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);

	}
	else if (Logic==EXT_FALLING)
	{
		CLEAR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
	}
	else if (Logic==EXT_ANY_LOGIC){
		SET_BIT(MCUCR,ISC00);
		CLEAR_BIT(MCUCR,ISC01);
	}

	//enable
	SET_BIT(GICR,INT0);

}


void EXT_int1Int(u8 Logic){
	if (Logic==EXT_RISING)
	{
		SET_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
	}
	else if (Logic==EXT_FALLING)
	{
		CLEAR_BIT(MCUCR,ISC10);
		CLEAR_BIT(MCUCR,ISC11);
	}
	else if (Logic==EXT_ANY_LOGIC){
		SET_BIT(MCUCR,ISC10);
		CLEAR_BIT(MCUCR,ISC11);
	}

	//enable
	SET_BIT(GICR,INT1);
}


void EXT_int2Int(u8 Logic){
	if (Logic==EXT_RISING)
	{
		SET_BIT(MCUCSR,ISC2);
	}
	else if (Logic==EXT_FALLING)
	{
		CLEAR_BIT(MCUCSR,ISC2);
	}

	//enable
	SET_BIT(GICR,INT2);
}


//Vector 1
void (*EXT_int0Func)();

//call back function to send the function from the main function
void EXT_setcallbackInt0(void (*ptr)()){
	EXT_int0Func = ptr;
}

//Vector Table Function that belongs to INT0
//number(in vector table) - 1
void __vector_1() __attribute__((signal));
void __vector_1(){
	EXT_int0Func();
	//LCD_Shift(LCD_SHIFT_DIS_LIFT);
}

//Vector 2
void (*EXT_int1Func)();

//call back function to send the function from the main function
void EXT_setcallbackInt1(void (*ptr)()){
	EXT_int1Func = ptr;
}

//Vector Table Function that belongs to INT1
//number(in vector table) - 1
void __vector_2() __attribute__((signal));
void __vector_2(){
	EXT_int1Func();
}


//Vector 3
void (*EXT_int2Func)();

//call back function to send the function from the main function
void EXT_setcallbackInt2(void (*ptr)()){
	EXT_int2Func = ptr;
}

//Vector Table Function that belongs to INT2
//number(in vector table) - 1
void __vector_3() __attribute__((signal));
void __vector_3(){
	EXT_int2Func();
}

