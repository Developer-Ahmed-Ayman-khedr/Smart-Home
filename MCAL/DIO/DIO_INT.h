/*
 * DIO_INT.h
 *
 *  Created on: May 16, 2024
 *      Author: ahmed
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

/******************************************
  INCLUDES
*******************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

//Set Cristal Frequency
#define F_CPU 16000000UL
#include<util/delay.h>

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/

//State
#define DIO_HIGH 1
#define DIO_LOW  0

//Direction
#define DIO_INPUT 0
#define DIO_OUTPUT 1

//Registers************************

//Port A
#define DDRA  (*(volatile u8*)0x3A)
#define PORTA (*(volatile u8*)0x3B)
#define PINA  (*(volatile u8*)0x39)

//Port B
#define DDRB  (*(volatile u8*)0x37)
#define PORTB (*(volatile u8*)0x38)
#define PINB  (*(volatile u8*)0x36)

//Port C
#define DDRC  (*(volatile u8*)0x34)
#define PORTC (*(volatile u8*)0x35)
#define PINC  (*(volatile u8*)0x33)

//Port D
#define DDRD  (*(volatile u8*)0x31)
#define PORTD (*(volatile u8*)0x32)
#define PIND  (*(volatile u8*)0x30)

//Pins******************************

//PINA
#define DIO_PINA0 0
#define DIO_PINA1 1
#define DIO_PINA2 2
#define DIO_PINA3 3
#define DIO_PINA4 4
#define DIO_PINA5 5
#define DIO_PINA6 6
#define DIO_PINA7 7

//PINB
#define DIO_PINB0 8
#define DIO_PINB1 9
#define DIO_PINB2 10
#define DIO_PINB3 11
#define DIO_PINB4 12
#define DIO_PINB5 13
#define DIO_PINB6 14
#define DIO_PINB7 15

//PINC
#define DIO_PINC0 16
#define DIO_PINC1 17
#define DIO_PINC2 18
#define DIO_PINC3 19
#define DIO_PINC4 20
#define DIO_PINC5 21
#define DIO_PINC6 22
#define DIO_PINC7 23

//PIND
#define DIO_PIND0 24
#define DIO_PIND1 25
#define DIO_PIND2 26
#define DIO_PIND3 27
#define DIO_PIND4 28
#define DIO_PIND5 29
#define DIO_PIND6 30
#define DIO_PIND7 31


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void DIO_setPinDir(u8 pinNum, u8 dir);

void DIO_setPinValue(u8 pinNum, u8 level);

u8 DIO_readPinValue(u8 pinNum);

void DIO_togglePinValue(u8 pinNum);

void DIO_setPullUp(u8 pinNum);


#endif /* MCAL_DIO_DIO_INT_H_ */
