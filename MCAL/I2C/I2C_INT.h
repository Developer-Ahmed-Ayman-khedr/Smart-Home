/*
 * I2C_INT.h
 *
 *  Created on: May 30, 2024
 *      Author: DELL
 */

#ifndef MCAL_I2C_I2C_INT_H_
#define MCAL_I2C_I2C_INT_H_

/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"
#include"STD_TYPES.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

#define I2C_SLAVE_ADDRESS  0x50

/*I2c Registers*/
#define TWBR            *((volatile u8*)(0x20))

#define TWCR            *((volatile u8*)(0x56))
#define TWINT     7
#define TWEA      6
#define TWSTA     5
#define TWSTO     4
#define TWWC      3
#define TWEN      2
#define TWIE      0

#define TWSR            *((volatile u8*)(0x21))
#define TWPS0  0
#define TWPS1  1
#define TWS3   3
#define TWS4   4
#define TWS5   5
#define TWS6   6
#define TWS7   7

#define TWDR            *((volatile u8*)(0x23))
#define TWD0   0

#define TWAR             *((volatile u8*)(0x22))
#define TWGCE

typedef enum i2c_mode
{
  SLAVE = 0,
  MASTER = 1
}I2C_mode;

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void I2C_init(I2C_mode mode);

void I2C_sendByte(u8 byte, u8 address);

void I2C_receiveByteACK(u8* byte, u8 address);

void I2C_receiveByteNACK(u8* byte, u8 address);

void I2C_SlaveReceiveByte(u8* byte);

#endif /* MCAL_I2C_I2C_INT_H_ */
