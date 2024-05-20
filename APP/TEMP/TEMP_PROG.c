/*
 * TEMP_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "TEMP_INT.h"

void TEMP_Init(){
	//ADC
	DIO_setPinDir(DIO_PINA1,DIO_INPUT);

	ADC_init();
	//DC Motor control

	//Enable
	DIO_setPinDir(DIO_PIND5,DIO_OUTPUT);

	//Direction
	DIO_setPinDir(DIO_PIND3,DIO_OUTPUT);
	DIO_setPinDir(DIO_PIND7,DIO_OUTPUT);

}

u16 VDigitalTemp, VAnalogTemp;

void TEMP_Check(){

	VDigitalTemp = ADC_read(ADC_CH1);
	VAnalogTemp = ADC_convertAnalog(VDigitalTemp);
	LCD_sendStr("Temperature = ");
	LCD_sendFloatNum(VAnalogTemp);
	LCD_sendStr(" C");
	TEMP_ControlAC();
}


void TEMP_ControlAC(){
	if(VAnalogTemp>28){

		//Enable
		DIO_setPinValue(DIO_PINA0,DIO_HIGH);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_HIGH);
		DIO_setPinValue(DIO_PIND7,DIO_LOW);
	}
	else if(VAnalogTemp<28){

			//Enable
		DIO_setPinValue(DIO_PINA0,DIO_LOW);

			//Direction
		DIO_setPinValue(DIO_PIND3,DIO_LOW);
		DIO_setPinValue(DIO_PINC6,DIO_LOW);
	}
}
