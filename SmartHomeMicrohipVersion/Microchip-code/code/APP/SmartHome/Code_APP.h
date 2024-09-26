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

#include "event_groups.h"

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

//Temperature Check

#define OUTPUTLCD 0

#define OUTPUTUART 1

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

//Lighting
#define LIGHTINGENTRANCE  '1'

#define LIGHTINHALL   '2'

//User
#define MAXUSERNUM  4

#define MINEEPROMUSER   4

#define MAXEEPROMUSER   24


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/
//Admin
void password_init ();

BOOL CheckPasswordAdmin();

//Temperature

void TEMP_Check(u8 Platform);

//Lighting

void LIGHTING_Start(u8 Start);

//Servo
void HOLD_init();

void HOLD_Start();

u32 HOLD_Retrun();

//Door
void DOORCONTROL_init();

void DOORCONTROL_Start();

//User
void AddUser();

void DeleteUser(u8 userID);

BOOL UserLogin();

//Main
void Code_APPInitDriversTask(void *pvParameters);

void LoginTask(void * pvParameters );

void AdminOptionsTask(void * pvParameters );

void UserOptionsTask(void * pvParameters );

//Source Code
int source_code();

#endif /* APP_CODE_APP_CODE_APP_H_ */
