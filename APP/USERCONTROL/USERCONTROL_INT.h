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
#include"INTERNALEEPROM_INT.h"
#include"KPD_INT.h"
#include"UART_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

#define MAXUSERNUM  4

#define MINEEPROMUSER   4

#define MAXEEPROMUSER   21

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void AddUser();

BOOL DeleteUser(u8 userID);

BOOL CheckDataForUser();

#endif /* APP_USERCONTROL_USERCONTROL_INT_H_ */
