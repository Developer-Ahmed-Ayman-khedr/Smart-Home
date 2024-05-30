/*
 * EEPROM_INT.h
 *
 *  Created on: May 30, 2024
 *      Author: DELL
 */

#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_

/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

#include "I2C_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void EEPROM_Init();

void EEPROM_SendByte(u8 byte,u16 location);

void EEPROM_ReadByteNACK(u8* byte,u16 location);


#endif /* HAL_EEPROM_EEPROM_INT_H_ */
