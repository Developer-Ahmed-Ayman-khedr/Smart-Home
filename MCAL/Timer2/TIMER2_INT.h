/*
 * TIMER2_INT.h
 *
 *  Created on: Aug 22, 2024
 *      Author: DELL
 */

#ifndef MCAL_TIMER2_TIMER2_INT_H_
#define MCAL_TIMER2_TIMER2_INT_H_


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
#define TCCR2 		*((volatile u8*)0x53)
#define FOC2		7
#define WGM20		6
#define COM21		5
#define COM20		4
#define WGM21		3
#define CS22		2
#define CS21		1
#define CS20		0

//Timer/Counter Register
#define TCNT2 		*((volatile u8*)0x52)

//Output Compare Register
#define OCR2 		*((volatile u8*)0x5C)

//Timer/Counter Interrupt Mask
#define TIMSK 		*((volatile u8*)0x59)
#define OCIE2		1
#define TOIE2		0


#define TIMER2_RISING	0
#define TIMER2_FALING	1

#define TIMER2_STOP			0
#define TIMER2_DIV0			1
#define TIMER2_DIV8			2
#define TIMER2_DIV32		3
#define TIMER2_DIV64		4
#define TIMER2_DIV128		5
#define TIMER2_DIV256		6
#define TIMER2_DIV1024		7


#define TIMER2_NON_INVERTED 0
#define TIMER2_INVERTED		1

#define TIMER2_PWM_mode TIMER2_NON_INVERTED

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void TIMER2_initNormal();

void TIMER2_setPreload(u8 value);

u8 TIMER2_getCounter();

void TIMER2_start(u8 prescaler);

void TIMER2_setCallbackOv(void (*ptr)());

//CTC
void TIMER2_initCTC();
void TIMER2_setOCR(u8 value);
void TIMER_setcallbackCTC(void (*ptr)());

//Fast PWM
void TIMER2_initFPWM();

//Phase correct PWM
void TIMER2_init_Phase_Correct_PWM();



#endif /* MCAL_TIMER2_TIMER2_INT_H_ */
