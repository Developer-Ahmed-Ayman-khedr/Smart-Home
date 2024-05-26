/*
 * KEYPAD_INT.h
 *
 *  Created on: May 19, 2024
 *      Author: ahmed
 */

#ifndef APP_INPUT_INPUT_INT_H_
#define APP_INPUT_INPUT_INT_H_

/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

#include "LCD_INT.h"

#include "KPD_INT.h"

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

void KEYPAD_Init();

u8 KEYPAD_Read();

#endif /* APP_INPUT_INPUT_INT_H_ */
