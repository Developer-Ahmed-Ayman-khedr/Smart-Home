/*
 * LIGHTING_PROG.c
 *
 *  Created on: May 25, 2024
 *      Author: Abdo
 */
#include "LIGHTING_INT.h"

void LIGHTING_init (){
	DIO_setPinDir(DIO_PINC0,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINC1,DIO_OUTPUT);

}




void LIGHTING_Start(u8 Start){
	switch(Start){
			case 1:
				 DIO_setPinValue (DIO_PINC0,DIO_HIGH);

				break;
			case 2:
				 DIO_setPinValue (DIO_PINC1,DIO_HIGH);
				break;
			default:
				break ;

	}

}
