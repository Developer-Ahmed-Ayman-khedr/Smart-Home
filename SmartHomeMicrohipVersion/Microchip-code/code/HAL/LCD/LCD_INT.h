/*
 * LCD_INT.h
 *
 * Created: 4/17/2024 6:14:47 PM
 *  Author: ahmed
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_


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

//Pin Configuration
#define LCD_D4 DIO_PINA4
#define LCD_D5 DIO_PINA5
#define LCD_D6 DIO_PINA6
#define LCD_D7 DIO_PINA7

#define LCD_E  DIO_PINB3
#define LCD_RS DIO_PINB1
#define LCD_RW DIO_PINB2

//Set send mode
#define LCD_DATA 0
#define LCD_CMD 1

//Shift configuration
#define LCD_SHIFT_DIS_RIGHT 0
#define LCD_SHIFT_DIS_LIFT 1


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

//Initialize
void LCD_init();

//Operation
void LCD_clearDis();

void LCD_GoTo(u8 x, u8 line );

void LCD_CreateNewCharacter(u8* ArrCustumCharachter, u8 CharLocation);

void LCD_Shift(u8 direction);

//Send
void LCD_sendData(u8 data);

void LCD_sendCmd(u8 cmd);

void LCD_sendStr(u8* str);

void LCD_sendNum(s32 num);

void LCD_sendFloatNum(f32 num);

void LCD_SendNewCharacter(u8 CharLocation);

#endif /* LCD_INT_H_ */