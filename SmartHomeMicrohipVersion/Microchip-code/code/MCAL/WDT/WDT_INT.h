/*
 * WDT_INT.h
 *
 * Created: 5/15/2024 7:24:14 PM
 *  Author: ahmed
 */ 


#ifndef WDT_INT_H_
#define WDT_INT_H_

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

//WDT Register
#define WDTCR (*(volatile u8*)0x41)


//Bits

//Control
#define WDE 3
#define WDTOE 4

//Time
#define WDP0 0
#define WDP1 1
#define WDP2 2

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

//Start WDT
void WDT_Start(u8 time);

//Stop WDT
void WDT_Stop();

#endif /* WDT_INT_H_ */