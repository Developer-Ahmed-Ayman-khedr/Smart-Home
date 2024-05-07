/*
 * KBD_PROG.c
 *
 * Created: 4/22/2024 6:46:45 PM
 *  Author: ahmed
 */ 
#include "KPD_INT.h"

//Initialize
void KPD_init()
{
	DIO_setPinDir(KPD_COL0, DIO_OUTPUT);
	DIO_setPinDir(KPD_COL1, DIO_OUTPUT);
	DIO_setPinDir(KPD_COL2, DIO_OUTPUT);
	DIO_setPinDir(KPD_COL3, DIO_OUTPUT);
	
	DIO_setPinDir(KPD_ROW0, DIO_INPUT);
	DIO_setPinDir(KPD_ROW1, DIO_INPUT);
	DIO_setPinDir(KPD_ROW2, DIO_INPUT);
	DIO_setPinDir(KPD_ROW3, DIO_INPUT);
	
	DIO_setPullUp(KPD_ROW0);
	DIO_setPullUp(KPD_ROW1);
	DIO_setPullUp(KPD_ROW2);
	DIO_setPullUp(KPD_ROW3);
	
}

//Read
u8 KPD_read()
{
	DIO_setPinValue(KPD_COL0, DIO_LOW);
	DIO_setPinValue(KPD_COL1, DIO_HIGH);
	DIO_setPinValue(KPD_COL2, DIO_HIGH);
	DIO_setPinValue(KPD_COL3, DIO_HIGH);
	
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
	DIO_setPinValue(KPD_COL3, DIO_HIGH);
	
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
	DIO_setPinValue(KPD_COL3, DIO_HIGH);
	
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
	
	DIO_setPinValue(KPD_COL0, DIO_HIGH);
	DIO_setPinValue(KPD_COL1, DIO_HIGH);
	DIO_setPinValue(KPD_COL2, DIO_HIGH);
	DIO_setPinValue(KPD_COL3, DIO_LOW);
	
	if(DIO_readPinValue(KPD_ROW0) == DIO_LOW)
	{
		return KPD_ROW0_COL3;
	}
	else if(DIO_readPinValue(KPD_ROW1) == DIO_LOW)
	{
		return KPD_ROW1_COL3;
	}
	else if(DIO_readPinValue(KPD_ROW2) == DIO_LOW)
	{
		return KPD_ROW2_COL3;
	}
	else if(DIO_readPinValue(KPD_ROW3) == DIO_LOW)
	{
		return KPD_ROW3_COL3;
	}
	
	return KPD_UNPRESSED;
}