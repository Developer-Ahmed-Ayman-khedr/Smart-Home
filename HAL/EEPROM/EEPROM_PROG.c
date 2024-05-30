/*
 * EEPROM_PROG.c
 *
 *  Created on: May 30, 2024
 *      Author: DELL
 */

#include "EEPROM_INT.h"

void EEPROM_Init()
{
	I2C_init(MASTER);
}

void EEPROM_SendByte(u8 byte,u16 location)
{
    //Send Start
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (GET_BIT(TWCR,TWINT)==0);

    //Send Location
    u8 varr = 0b10100000|(location>>7);
    CLEAR_BIT(varr,0);
    TWDR = varr;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (GET_BIT(TWCR,TWINT)==0);

    //Send the remainder of Location
    TWDR = (u8)location;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (GET_BIT(TWCR,TWINT)==0);

    //Send Data
    TWDR = byte;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (GET_BIT(TWCR,TWINT)==0);

    //Send Stop
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void EEPROM_ReadByteNACK(u8* byte,u16 location){
  //Send Dummy Write Start
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Location
  u8 varr = 0b10100000|(location>>7);
  CLEAR_BIT(varr,0);
  TWDR = varr;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send the remainder of Location
  TWDR = (u8)location;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Start
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Location
  SET_BIT(varr,0);
  TWDR = varr;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Read data
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);
  *byte = TWDR;

  //Send Stop
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
