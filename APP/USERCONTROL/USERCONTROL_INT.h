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

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

#define MAXUSERNUM  4

#define MAXPASSNUM  4

#define MINEEPROMUSER   '100'

#define MAXEEPROMUSER   '116'

#define MINEEPROMPASS   '117'

#define MAXEEPROMPASS   '132'




/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void AddUserName();

void AddPassword();

u8 DeleteUser();

#endif /* APP_USERCONTROL_USERCONTROL_INT_H_ */
