/*
 * TEMP_PROG.c
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#include "TEMP_INT.h"

void TEMP_Init(){
	DIO_setPinDir(DIO_PINA1,DIO_INPUT);
	ADC_init();
}

void TEMP_Check(){

	u16 vtemp = ADC_read(ADC_CH1);

	LCD_sendStr("Temp = ");
	LCD_sendFloatNum(ADC_convertAnalog(vtemp));
	LCD_sendStr(" C");
}


void TEMP_SendToAC(){

}
