/*
 * INTERNALEEPROM_INT.h
 *
 * Created: 8/5/2024 7:54:35 PM
 *  Author: ahmed
 */ 


#ifndef INTERNALEEPROM_INT_H_
#define INTERNALEEPROM_INT_H_


/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

//Enable INTERNALEEPROM
/*if INTERNALEEPROM == 0x0 then it is disabled.*/

/*if INTERNALEEPROM == 0x1 then it is enabled.*/

#define INTERNALEEPROM 0x1

//Registers
//Address
#define EEAR (*(volatile u16*)0x3E)

//Data
#define EEDR (*(volatile u8*)0x3D)

//Control
#define EECR (*(volatile u8*)0x3C)

//Bits
#define EEMWE 2 /*EEPROM Master Write Enable*/

#define EEWE 1 /*EEPROM Write Enable*/

#define EERE 0 /*EEPROM Read Enable*/

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

#if (INTERNALEEPROM==0x1)

void INTERNALEEPROM_SendByte(u8 byte,u16 location);

u8 INTERNALEEPROM_Read(u16 location);

#endif



#endif /* INTERNALEEPROM_INT_H_ */
