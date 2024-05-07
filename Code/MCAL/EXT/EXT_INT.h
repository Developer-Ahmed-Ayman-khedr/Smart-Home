/*
 * EXT_INT.h
 *
 * Created: 4/24/2024 7:24:23 PM
 *  Author: ahmed
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_

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
//Register for INT0 & INT1
#define MCUCR  (*(volatile u8*)0x55)

//Needed Bits

//INT0
#define ISC00 0
#define ISC01 1

//INT1
#define ISC10 2
#define ISC11 3

//Register for INT2
#define MCUCSR  (*(volatile u8*)0x54)
//Needed Bits

//INT2
#define ISC2 6

//Enable PIE
#define GICR  (*(volatile u8*)0x5B)

//Needed Bits
#define INT0 6
#define INT1 7
#define INT2 5

//Interrupt Logic
#define EXT_FALLING    0
#define EXT_RISING     1
#define EXT_ANY_LOGIC  2


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

//Initialize
void EXT_int0Int(u8 Logic);

void EXT_int1Int(u8 Logic);

void EXT_int2Int(u8 Logic);

//Call back
void EXT_setcallbackInt0(void (*ptr)());

void EXT_setcallbackInt1(void (*ptr)());

void EXT_setcallbackInt2(void (*ptr)());


#endif /* EXT_INT_H_ */