/*
 * Code_APP.h
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#ifndef APP_CODE_APP_CODE_APP_H_
#define APP_CODE_APP_CODE_APP_H_


/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

#include "ADC_INT.h"

#include "LCD_INT.h"

#include "KPD_INT.h"

#include "GI_INT.h"

#include "EXT_INT.h"

#include "TIMER0_INT.h"

#include "TIMER1_INT.h"

#include "HOLD_INT.h"

#include "TEMP_INT.h"

#include "PasswordCheck_INT.h"

#include "LIGHTING_INT.h"

#include "DOORCONTROL_INT.h"

#include "INPUT_INT.h"

#include "UART_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

#define RETURN 1

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void Code_APPInitDrivers();

void Code_APP();

#endif /* APP_CODE_APP_CODE_APP_H_ */
