/*
 * GI_INT.h
 *
 *  Created on: May 16, 2024
 *      Author: ahmed
 */

#ifndef MCAL_GI_GI_INT_H_
#define MCAL_GI_GI_INT_H_


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


#endif /* MCAL_GI_GI_INT_H_ */
