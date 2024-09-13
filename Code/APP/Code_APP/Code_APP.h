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

//Physical Drivers

#include "DIO_INT.h"

#include "ADC_INT.h"

#include "GI_INT.h"

#include "EXT_INT.h"

#include "TIMER0_INT.h"

#include "TIMER1_INT.h"

#include "UART_INT.h"

#include "INTERNALEEPROM_INT.h"

#include "LCD_INT.h"

#include "KPD_INT.h"

//FreeRTOS

#include "FreeRTOS.h"

#include "FreeRTOSConfig.h"

#include "task.h"

//Project Elements

#include "DOORCONTROL_INT.h"

#include "HOLD_INT.h"

#include "LIGHTING_INT.h"

#include "PasswordCheck_INT.h"

#include "TEMP_INT.h"

#include "USERCONTROL_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/

TaskHandle_t Code_APPInitDriversTaskHandle;

TaskHandle_t LoginTaskHandle;

TaskHandle_t AdminOptionsTaskHandle;

TaskHandle_t UserOptionsTaskHandle;

/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

//Input
#define INPUT_Light	'1'

#define INPUT_Temp 	'2'

#define INPUT_ENTERANCE '3'

#define INPUT_ADDUSER  '4'

#define INPUT_DELETEUSER  '5'

#define INPUT_RETURN '1'

#define INPUT_LIGHTINGROOM '1'

#define INPUT_LIGHTINHALL '2'

//Admin
#define INPUT_LOGOUTADMIN '6'

//User
#define INPUT_LOGOUTUSER '4'

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void Code_APPInitDriversTask(void *pvParameters);

void LoginTask(void * pvParameters );

void AdminOptionsTask(void * pvParameters );

void UserOptionsTask(void * pvParameters );

#endif /* APP_CODE_APP_CODE_APP_H_ */
