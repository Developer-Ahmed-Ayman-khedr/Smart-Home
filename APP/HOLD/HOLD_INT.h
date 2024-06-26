/*
 * HOLD_INT.h
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#ifndef APP_HOLD_HOLD_INT_H_
#define APP_HOLD_HOLD_INT_H_


/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

#include "GI_INT.h"

#include "TIMER0_INT.h"

#include "EXT_INT.h"

#include "LCD_INT.h"

#include "UART_INT.h"

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

void HOLD_init();

void HOLD_Start();

u32 HOLD_Retrun();

#endif /* APP_HOLD_HOLD_INT_H_ */
