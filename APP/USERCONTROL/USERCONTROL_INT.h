/*
 * USERCONTROL_INT.h
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */

#ifndef APP_USERCONTROL_USERCONTROL_INT_H_
#define APP_USERCONTROL_USERCONTROL_INT_H_

/**************
  INCLUDES
***************/

#include "STD_TYPES.h"
#include"LCD_INT.h"
#include"EEPROM_INT.h"
#include"KPD_INT.h"
#include"UART_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

#define MAXUSERNUM  4

#define MINEEPROMUSER   100

#define MAXEEPROMUSER   132




/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void AddUser();

BOOL DeleteUser();

BOOL CheckDataForUser();

#endif /* APP_USERCONTROL_USERCONTROL_INT_H_ */
