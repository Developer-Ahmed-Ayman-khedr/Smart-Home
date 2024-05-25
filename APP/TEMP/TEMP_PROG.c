/*
 * TEMP_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "TEMP_INT.h"

void TEMP_Init(){
	//ADC
	ADC_init();

	DIO_setPinDir(DIO_PINA1,DIO_INPUT);

	//DC Motor control

	//Enable
	DIO_setPinDir(DIO_PIND4,DIO_OUTPUT);

	//Direction
	DIO_setPinDir(DIO_PIND3,DIO_OUTPUT);
	DIO_setPinDir(DIO_PIND7,DIO_OUTPUT);

}

u16 VDigitalTemp;
f32 VAnalogTemp;

void TEMP_Check(){

	VDigitalTemp = ADC_read(ADC_CH1);
	VAnalogTemp = (ADC_convertAnalog(VDigitalTemp))*100;
	LCD_clearDis();
	LCD_sendStr("Temp = ");
	LCD_sendFloatNum(VAnalogTemp);
	LCD_sendData('C');
	TEMP_ControlAC();
}


void TEMP_ControlAC(){
	if(VAnalogTemp>28){

		//Enable
		DIO_setPinValue(DIO_PIND4,DIO_HIGH);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_HIGH);
		DIO_setPinValue(DIO_PIND7,DIO_LOW);
	}
	else if(VAnalogTemp<28){

		//Enable
		DIO_setPinValue(DIO_PIND4,DIO_LOW);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_LOW);
		DIO_setPinValue(DIO_PINC6,DIO_LOW);
	}
}
