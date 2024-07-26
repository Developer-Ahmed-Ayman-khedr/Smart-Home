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

#include "LCD_INT.h"

#include "KPD_INT.h"

#include "GI_INT.h"

#include "EXT_INT.h"

#include "TIMER0_INT.h"

#include "TIMER1_INT.h"

#include "UART_INT.h"

#include "I2C_INT.h"

#include "EEPROM_INT.h"

//FreeRTOS

#include "FreeRTOS.h"

#include "FreeRTOSConfig.h"

#include "task.h"

#include "semphr.h"

#include "event_groups.h"

#include "queue.h"

//Project Elements

#include "DOORCONTROL_INT.h"

#include "HOLD_INT.h"

#include "INPUT_INT.h"

#include "LIGHTING_INT.h"

#include "PasswordCheck_INT.h"

#include "TEMP_INT.h"

#include "USERCONTROL_INT.h"

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/

EventGroupHandle_t LoginEventGroup;

QueueHandle_t xQueue;

EventBits_t uxBits;

SemaphoreHandle_t A;

TaskHandle_t Code_APPInitDriversTaskHandle;
TaskHandle_t UARTInputTaskHandle;
TaskHandle_t LoginTaskHandle;
TaskHandle_t OptionsTaskHandle;
TaskHandle_t DoorControlTaskHandle;

/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

#define INPUT_Light	'1'

#define INPUT_Temp 	'2'

#define INPUT_ENTERANCE '3'

#define RETURN 1

//Input
#define INPUT_LIGHTINGROOM '1'

#define INPUT_LIGHTINHALL '2'

#define INPUT_return '1'

// Specific for Event Group in Login System
#define BIT_0	( 1 << 0 )

//Lighting
#define LIGHTINGROOM  1

#define LIGHTINHALL   2

//User
#define MAXUSERNUM  4

#define MINEEPROMUSER   100

#define MAXEEPROMUSER   132

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void Code_APPInitDriversTask(void *pvParameters);

void UARTInputTask(void *pvParameters);

void LoginTask(void * pvParameters );

void OptionsTask(void *pvParameters);

void DoorControlTask (void * pvParameters );

#endif /* APP_CODE_APP_CODE_APP_H_ */
