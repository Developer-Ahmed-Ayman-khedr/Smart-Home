/*
 * KPAD_INT.h
 *
 *  Created on: May 16, 2024
 *      Author: Abdo
 */

#ifndef HAL_KPD_KPAD_INT_H_
#define HAL_KPD_KPAD_INT_H_

/**************
  INCLUDES
***************/

#include "DIO_INT.h"

/**************
  Global Data TYPES AND STRUCTURES
***************/


/**************
  GLOBAL CONSTANT MACROS
***************/

//Define Rows
#define KPD_ROW0	DIO_PINB4
#define KPD_ROW1	DIO_PINB5
#define KPD_ROW2	DIO_PINB6
#define KPD_ROW3	DIO_PINB7

//Define Columns
#define KPD_COL0	DIO_PINC3
#define KPD_COL1	DIO_PINC4
#define KPD_COL2	DIO_PINC5

//Define Buttons Row0
#define KPD_ROW0_COL0	'1'
#define KPD_ROW0_COL1	'2'
#define KPD_ROW0_COL2	'3'

//Define Buttons Row1
#define KPD_ROW1_COL0	'4'
#define KPD_ROW1_COL1	'5'
#define KPD_ROW1_COL2	'6'

//Define Buttons Row2
#define KPD_ROW2_COL0	'7'
#define KPD_ROW2_COL1	'8'
#define KPD_ROW2_COL2	'9'

//Define Buttons Row3
#define KPD_ROW3_COL0	'*'
#define KPD_ROW3_COL1	'0'
#define KPD_ROW3_COL2	'#'

//Define when unpressing a Button
#define KPD_UNPRESSED	'x'

/**************
  GLOBAL FUNCTIONS MACROS
***************/


/**************
  GLOBAL FUNCTIONS Prototypes
***************/

//Initialize
void KPD_init();

//Read
u8 KPD_read();

#endif /* HAL_KPD_KPAD_INT_H_ */
