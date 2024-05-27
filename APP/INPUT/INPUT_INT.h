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

#include "UART_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/


#define INPUT_Light	'1'

#define INPUT_Temp 	'2'


#define INPUT_LIGHTINGROOM '1'

#define INPUT_LIGHTINHALL '2'

#define INPUT_return '1'

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void INPUT_Init();

u8 INPUT_Read();

#endif /* APP_INPUT_INPUT_INT_H_ */
