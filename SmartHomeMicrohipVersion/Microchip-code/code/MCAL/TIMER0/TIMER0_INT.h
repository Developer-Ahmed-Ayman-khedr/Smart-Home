/*
 * TIMRE0_INT.h
 *
 * Created: 5/1/2024 7:35:19 PM
 *  Author: ahmed
 */ 


#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

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


//Timer/Counter Control Register
#define TCCR0 		*((volatile u8*)0x53)
#define FOC0		7
#define WGM00		6
#define COM01		5
#define COM00		4
#define WGM01		3
#define CS02		2
#define CS01		1
#define CS00		0

//Timer/Counter Register
#define TCNT0 		*((volatile u8*)0x52)

//Output Compare Register
#define OCR0 		*((volatile u8*)0x5C)

//Timer/Counter Interrupt Mask
#define TIMSK 		*((volatile u8*)0x59)
#define OCIE0		1
#define TOIE0		0


#define TIMER0_RISING	0
#define TIMER0_FALING	1

#define TIMER0_STOP			0
#define TIMER0_DIV0			1
#define TIMER0_DIV8			2
#define TIMER0_DIV64		3
#define TIMER0_DIV256		4
#define TIMER0_DIV1028		5
#define TIMER0_EXT_RISING	6

#define TIMER0_NON_INVERTED 0
#define TIMER0_INVERTED		1

#define TIMER0_PWM_mode TIMER0_NON_INVERTED

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void TIMER0_initNormal();

void TIMER0_setPreload(u8 value);

u8 TIMER0_getCounter();

void TIMER0_start(u8 prescaler);

void TIMER0_setCallbackOv(void (*ptr)());

//CTC
void TIMER0_initCTC();
void TIMER0_setOCR(u8 value);
void TIMER_setcallbackCTC(void (*ptr)());

//Fast PWM
void TIMER0_initFPWM();

//Phase correct PWM
void TIMER0_init_Phase_Correct_PWM();

#endif /* TIMRE0_INT_H_ */