/*
 * GIT_INT.h
 *
 * Created: 4/24/2024 7:49:02 PM
 *  Author: ahmed
 */ 


#ifndef GI_INT_H_
#define GI_INT_H_

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

//Register controlling Global Interrupt
#define SREG (*(volatile u8*)0x5F)

//Bits
#define I 7

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void GI_enable();

void GI_desable();

#endif /* GI_INT_H_ */