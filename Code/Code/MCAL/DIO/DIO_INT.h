/*
 * DIO_INT.h
 *
 * Created: 5/6/2024 8:07:28 PM
 *  Author: Abdo
 */ 


#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "STD_TYPES.h"

#define DDRA *(volatile u8*)0x3A // to compiler say the variable important
#define PORTA *(volatile u8*)0x3B
#define PINA *(volatile u8*)0x39

#define DDRB *(volatile u8*)0x37
#define PORTB *(volatile u8*)0x38
#define PINB (*(volatile u8*)0x36)

#define DDRC *(volatile u8*)0x34
#define PORTC *(volatile u8*)0x35
#define PINC *(volatile u8*)0x33

#define DDRD *(volatile u8*)0x31
#define PORTD *(volatile u8*)0x32
#define PIND *(volatile u8*)0x30

#define DIO_PINA0 0
#define DIO_PINA1 1
#define DIO_PINA2 2
#define DIO_PINA3 3
#define DIO_PINA4 4
#define DIO_PINA5 5
#define DIO_PINA6 6
#define DIO_PINA7 7

#define DIO_PINB0 8 //0
#define DIO_PINB1 9	//1
#define DIO_PINB2 10//2
#define DIO_PINB3 11
#define DIO_PINB4 12
#define DIO_PINB5 13
#define DIO_PINB6 14
#define DIO_PINB7 15

#define DIO_PINC0 16
#define DIO_PINC1 17
#define DIO_PINC2 18
#define DIO_PINC3 19
#define DIO_PINC4 20
#define DIO_PINC5 21
#define DIO_PINC6 22
#define DIO_PINC7 23

#define DIO_PIND0 24
#define DIO_PIND1 25
#define DIO_PIND2 26
#define DIO_PIND3 27
#define DIO_PIND4 28
#define DIO_PIND5 29
#define DIO_PIND6 30
#define DIO_PIND7 31


#define  DIO_HIGH 1
#define  DIO_LOW 0

#define DIO_OUTPUT 1
#define DIO_INPUT 0

void DIO_setPinValue(u8 pinNum, u8 level);
void DIO_setPinDir(u8 pinNum, u8 state);

u8 DIO_readPinValue(u8 pinNum);

void DIO_setPinPullUp(u8 pinNum);

void DIO_togglePin(u8 pinNum);




#endif /* DIO_INT_H_ */