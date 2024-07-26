/*
 * LIGHTING_INT.h
 *
 *  Created on: May 25, 2024
 *      Author: Abdo
 */

#ifndef APP_LIGHTING_LIGHTING_INT_H_
#define APP_LIGHTING_LIGHTING_INT_H_
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
#define LIGHTINGROOM  1

#define LIGHTINHALL   2

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/
void LIGHTING_init();
void LIGHTING_Start(u8 Start);


#endif /* APP_LIGHTING_LIGHTING_INT_H_ */
