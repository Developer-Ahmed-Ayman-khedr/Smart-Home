/*
 * KPAD_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: Abdo
 */

#include "../KPD/KPD_INT.h"

void KPD_init()
{
	DIO_setPinDir(KPD_COL0, DIO_OUTPUT);
	DIO_setPinDir(KPD_COL1, DIO_OUTPUT);
	DIO_setPinDir(KPD_COL2, DIO_OUTPUT);

	DIO_setPinDir(KPD_ROW0, DIO_INPUT);
	DIO_setPinDir(KPD_ROW1, DIO_INPUT);
	DIO_setPinDir(KPD_ROW2, DIO_INPUT);
	DIO_setPinDir(KPD_ROW3, DIO_INPUT);

	DIO_setPullUp(KPD_ROW0);
	DIO_setPullUp(KPD_ROW1);
	DIO_setPullUp(KPD_ROW2);
	DIO_setPullUp(KPD_ROW3);

}


u8 KPD_read()
{
	DIO_setPinValue(KPD_COL0, DIO_LOW);
	DIO_setPinValue(KPD_COL1, DIO_HIGH);
	DIO_setPinValue(KPD_COL2, DIO_HIGH);

	if(DIO_readPinValue(KPD_ROW0) == DIO_LOW)
	{
		return KPD_ROW0_COL0;
	}
	else if(DIO_readPinValue(KPD_ROW1) == DIO_LOW)
	{
		return KPD_ROW1_COL0;
	}
	else if(DIO_readPinValue(KPD_ROW2) == DIO_LOW)
	{
		return KPD_ROW2_COL0;
	}
	else if(DIO_readPinValue(KPD_ROW3) == DIO_LOW)
	{
		return KPD_ROW3_COL0;
	}

	DIO_setPinValue(KPD_COL0, DIO_HIGH);
	DIO_setPinValue(KPD_COL1, DIO_LOW);
	DIO_setPinValue(KPD_COL2, DIO_HIGH);

	if(DIO_readPinValue(KPD_ROW0) == DIO_LOW)
	{
		return KPD_ROW0_COL1;
	}
	else if(DIO_readPinValue(KPD_ROW1) == DIO_LOW)
	{
		return KPD_ROW1_COL1;
	}
	else if(DIO_readPinValue(KPD_ROW2) == DIO_LOW)
	{
		return KPD_ROW2_COL1;
	}
	else if(DIO_readPinValue(KPD_ROW3) == DIO_LOW)
	{
		return KPD_ROW3_COL1;
	}


	DIO_setPinValue(KPD_COL0, DIO_HIGH);
	DIO_setPinValue(KPD_COL1, DIO_HIGH);
	DIO_setPinValue(KPD_COL2, DIO_LOW);

	if(DIO_readPinValue(KPD_ROW0) == DIO_LOW)
	{
		return KPD_ROW0_COL2;
	}
	else if(DIO_readPinValue(KPD_ROW1) == DIO_LOW)
	{
		return KPD_ROW1_COL2;
	}
	else if(DIO_readPinValue(KPD_ROW2) == DIO_LOW)
	{
		return KPD_ROW2_COL2;
	}
	else if(DIO_readPinValue(KPD_ROW3) == DIO_LOW)
	{
		return KPD_ROW3_COL2;
	}

	return KPD_UNPRESSED;
}
