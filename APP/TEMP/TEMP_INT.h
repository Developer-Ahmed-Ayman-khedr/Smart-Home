/*
 * TEMP_INT.h
 *
 *  Created on: May 17, 2024
 *      Author: ahmed
 */

#ifndef APP_TEMP_TEMP_INT_H_
#define APP_TEMP_TEMP_INT_H_

/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

#include "ADC_INT.h"

#include "LCD_INT.h"

#include "TIMER1_INT.h"

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

void TEMP_Init();

void TEMP_Check();

void TEMP_ControlAC();

#endif /* APP_TEMP_TEMP_INT_H_ */
