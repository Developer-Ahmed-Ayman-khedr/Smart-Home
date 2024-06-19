/*
 * PasswordCheck.h
 *
 *  Created on: May 18, 2024
 *      Author: Abdo
 */

#ifndef APP_PASSWORDCHECK_PASSWORDCHECK_INT_H_
#define APP_PASSWORDCHECK_PASSWORDCHECK_INT_H_
/**************
  INCLUDES
***************/
#include "DIO_INT.h"
#include "LCD_INT.h"
#include "KPD_INT.h"

#include "UART_INT.h"

#include "EEPROM_INT.h"

#include"I2C_INT.h"
/**************
  Global Data TYPES AND STRUCTURES
***************/

typedef struct node
{
    u8 start_address_user;
    u8 end_address_user;
    u8 start_address_pass;
    u8 end_address_pass;
    struct node* next;
 }NODE;

 NODE* Head = NULL ;

/**************
  GLOBAL CONSTANT MACROS
***************/


/**************
  GLOBAL FUNCTIONS MACROS
***************/


/**************
  GLOBAL FUNCTIONS Prototypes
***************/
void password_init ();
void CheckPassword (u8* Ma_Fl_ptr);


#endif /* APP_PASSWORDCHECK_PASSWORDCHECK_INT_H_ */
