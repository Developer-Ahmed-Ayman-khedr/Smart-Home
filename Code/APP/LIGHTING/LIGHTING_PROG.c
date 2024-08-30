/*
 * LIGHTING_PROG.c
 *
 *  Created on: May 25, 2024
 *      Author: Abdo
 */
#include "LIGHTING_INT.h"

void LIGHTING_Start(u8 Start){

	DIO_setPinDir(DIO_PINC2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINC7,DIO_OUTPUT);

	if (Start==LIGHTINGROOM)
	{
		DIO_togglePinValue(DIO_PINC7);
	}
	else if (Start==LIGHTINHALL)
	{
		DIO_togglePinValue(DIO_PINC2);
	}
}
