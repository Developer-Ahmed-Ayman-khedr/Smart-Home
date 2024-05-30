/*
 * I2C_PROG.c
 *
 *  Created on: May 30, 2024
 *      Author: DELL
 */

#include "I2C_INT.h"

void I2C_init(I2C_mode mode){
  if (mode==MASTER)
  {
  }
  else if (mode==SLAVE)
  {
    TWAR = I2C_SLAVE_ADDRESS<<1;
  }

  //Enable
  SET_BIT(TWCR,TWEN);
  TWBR = 72;
}

void I2C_sendByte(u8 byte, u8 address){

  //Send Start
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Address
  u8 varr = (address<<1);
  CLEAR_BIT(varr,0);
  TWDR = varr;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Data
  TWDR = byte;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Stop
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}

void I2C_receiveByteACK(u8* byte, u8 address){

  //Send Start
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Address
  u8 varr = (address<<1);
  CLEAR_BIT(varr,0);
  TWDR = varr;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Read data
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
  while (GET_BIT(TWCR,TWINT)==0);
  *byte = TWDR;

  //Send Stop
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}


void I2C_receiveByteNACK(u8* byte, u8 address){
  //Send Start
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (GET_BIT(TWCR,TWINT)==0);

  //Send Address
  u8 varr = (address<<1);
  CLEAR_BIT(varr,0);
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


void I2C_SlaveReceiveByte(u8* byte){

  //Read data
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWEA);
  while (GET_BIT(TWCR,TWINT)==0);
  *byte = TWDR;
}
