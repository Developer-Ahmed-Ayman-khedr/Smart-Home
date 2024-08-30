/*
 * InternalEEPROM_PROG.c
 *
 * Created: 8/5/2024 7:54:53 PM
 *  Author: ahmed
 */ 

#include "INTERNALEEPROM_INT.h"

#if (INTERNALEEPROM==0x1)

void INTERNALEEPROM_SendByte(u8 byte,u16 location){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = location;
	EEDR = byte;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start EEPROM write by setting EEWE */
	EECR |= (1<<EEWE);
}

u8 INTERNALEEPROM_Read(u16 location){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = location;
	/* Start EEPROM read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

#endif