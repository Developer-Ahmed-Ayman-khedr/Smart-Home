/*
 * ADC_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: DELL
 */


#include "ADC_INT.h"

void ADC_init()
{
	//select Vref -> AVCC

	SET_BIT(ADMUX, REFS0);
	CLEAR_BIT(ADMUX, REFS1);

	//prescaler select 128

	SET_BIT(ADCSRA,ADPS0) ;
	SET_BIT(ADCSRA,ADPS1) ;
	SET_BIT(ADCSRA,ADPS2) ;


	//enable ADC

	SET_BIT(ADCSRA,ADEN) ;
}

u16 ADC_read(u8 chNum)
{
	//select ch.
	if(chNum == ADC_CH0)
	{
		CLEAR_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		CLEAR_BIT(ADMUX, MUX4);

	}
	else if(chNum == ADC_CH1)
	{
		SET_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		CLEAR_BIT(ADMUX, MUX4);
	}

	//start

	SET_BIT(ADCSRA,ADSC) ;
	//wait conv.
	while(GET_BIT(ADCSRA ,ADSC) == 1);

	//read
	return ADCLH;
}

f32 ADC_convertAnalog(u16 digitalValue)
{
	f32 analog = digitalValue * (5.0/1024);
	return analog;
}
