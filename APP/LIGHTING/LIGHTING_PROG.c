/*
 * LIGHTING_PROG.c
 *
 *  Created on: May 25, 2024
 *      Author: Abdo
 */
#include "LIGHTING_INT.h"

void LIGHTING_init (){
	DIO_setPinDir(DIO_PINC2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINC7,DIO_OUTPUT);

}




void LIGHTING_Start(u8 Start){
	switch(Start){
			case LIGHTINGROOM:
				 DIO_togglePinValue(DIO_PINC7);
				break;
			case LIGHTINHALL:
				 DIO_togglePinValue(DIO_PINC2);
				break;
			default:
				break ;

	}



}
