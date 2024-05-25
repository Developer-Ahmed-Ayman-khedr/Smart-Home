/*
 * DOORCONTROL_INT.h
 *
 *  Created on: May 25, 2024
 *      Author: ahmed
 */

#ifndef APP_DOORCONTROL_DOORCONTROL_INT_H_
#define APP_DOORCONTROL_DOORCONTROL_INT_H_

/******************************************
  INCLUDES
*******************************************/

#include "DIO_INT.h"

#include "GI_INT.h"

#include "TIMER1_INT.h"

#include "HOLD_INT.h"

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

void DOORCONTROL_init();

void DOORCONTROL_Start(u8* Ma_Fl_ptr);

#endif /* APP_DOORCONTROL_DOORCONTROL_INT_H_ */
