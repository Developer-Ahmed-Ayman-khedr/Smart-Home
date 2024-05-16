/*
 * WDT_INT.h
 *
 *  Created on: May 16, 2024
 *      Author: DELL
 */

#ifndef MCAL_WDT_WDT_INT_H_
#define MCAL_WDT_WDT_INT_H_

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
#define WDTCR *(volatile u8*)0x41
#define WDP0		0
#define WDP1		1
#define WDP2		2
#define WDE			3
#define WDTOE		4


#define WDT_TIME0	0
#define WDT_TIME1	1
#define WDT_TIME2	2
#define WDT_TIME3	3
#define WDT_TIME4	4
#define WDT_TIME5	5
#define WDT_TIME6	6
#define WDT_TIME7	7

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/
void WDT_start(u8 time);

void WDT_stop();

#endif /* MCAL_WDT_WDT_INT_H_ */
