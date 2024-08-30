/*
 * DIO_PORG.c
 *
 *  Created on: May 16, 2024
 *      Author: ahmed
 */

#include "DIO_INT.h"

void DIO_setPinDir(u8 pinNum, u8 dir){
	//PORTA
	if (pinNum>=0 && pinNum<=7)
	{
		if (dir==DIO_INPUT){
			CLEAR_BIT(DDRA,pinNum);
		}
		else if(dir==DIO_OUTPUT){
			SET_BIT(DDRA,pinNum);
		}
	}
	else //PORTB
	if (pinNum>=8 && pinNum<=15)
	{
		pinNum=pinNum-8;
		if (dir==DIO_INPUT){
			CLEAR_BIT(DDRB,pinNum);
		}
		else if(dir==DIO_OUTPUT){
			SET_BIT(DDRB,pinNum);
		}
	}
	else //PORTC
	if (pinNum>=16 && pinNum<=23)
	{
		pinNum=pinNum-16;
		if (dir==DIO_INPUT){
			CLEAR_BIT(DDRC,pinNum);
		}
		else if(dir==DIO_OUTPUT){
			SET_BIT(DDRC,pinNum);
		}
	}
	else //PORTD
	if (pinNum>=24 && pinNum<=31)
	{
		pinNum=pinNum-24;
		if (dir==DIO_INPUT){
			CLEAR_BIT(DDRD,pinNum);
		}
		else if(dir==DIO_OUTPUT){
			SET_BIT(DDRD,pinNum);
		}
	}
}

void DIO_setPinValue(u8 pinNum, u8 level){
	//PORTA
	if (pinNum>=0 && pinNum<=7)
	{
		if (level==DIO_LOW){
			CLEAR_BIT(PORTA,pinNum);
		}
		else if(level==DIO_HIGH){
			SET_BIT(PORTA,pinNum);
		}
	}
	else //PORTB
	if (pinNum>=8 && pinNum<=15)
	{
		pinNum=pinNum-8;
		if (level==DIO_LOW){
			CLEAR_BIT(PORTB,pinNum);
		}
		else if(level==DIO_HIGH){
			SET_BIT(PORTB,pinNum);
		}
	}
	else //PORTC
	if (pinNum>=16 && pinNum<=23)
	{
		pinNum=pinNum-16;
		if (level==DIO_LOW){
			CLEAR_BIT(PORTC,pinNum);
		}
		else if(level==DIO_HIGH){
			SET_BIT(PORTC,pinNum);
		}
	}
	else //PORTD
	if (pinNum>=24 && pinNum<=31)
	{
		pinNum=pinNum-24;
		if (level==DIO_LOW){
			CLEAR_BIT(PORTD,pinNum);
		}
		else if(level==DIO_HIGH){
			SET_BIT(PORTD,pinNum);
		}
	}
}

u8 DIO_readPinValue(u8 pinNum){
	//PORTA
	if (pinNum>=0 && pinNum<=7)
	{
		return GET_BIT(PINA,pinNum);
	}
	else //PORTB
	if (pinNum>=8 && pinNum<=15)
	{
		pinNum=pinNum-8;
		return GET_BIT(PINB,pinNum);
	}
	else //PORTC
	if (pinNum>=16 && pinNum<=23)
	{
		pinNum=pinNum-16;
		return GET_BIT(PINC,pinNum);
	}
	else //PORTD
	if (pinNum>=24 && pinNum<=31)
	{
		pinNum=pinNum-24;
		return GET_BIT(PIND,pinNum);
	}
}

void DIO_togglePinValue(u8 pinNum){
	DIO_setPinValue(pinNum,!DIO_readPinValue(pinNum));
}

void DIO_setPullUp(u8 pinNum){
	DIO_setPinValue(pinNum,DIO_HIGH);
}
