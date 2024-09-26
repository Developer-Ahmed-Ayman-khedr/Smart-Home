/*
 * TIMER1_INT.h
 *
 * Created: 5/13/2024 9:02:41 PM
 *  Author: ahmed
 */ 


#ifndef TIMER1_INT_H_
#define TIMER1_INT_H_


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

#define TIMER1_PWM_INVERTING 	 0
#define TIMER1_PWM_NON_INVERTING 1
#define TIMER1_PWM_MODE 		 TIMER1_PWM_NON_INVERTING


////////////////////////////////////////////////////////////////////////

/*TIMER1 Registers*/
#define TCCR1A				*((volatile u8*)0x4F)
#define WGM10	0
#define WGM11	1
#define FOC1A	2
#define FOC1B	3
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6
#define COM1A1	7

#define TCCR1B				*((volatile u8*)0x4E)
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4
#define ICES1	6
#define ICNC1	7

#define TCNT1				*((volatile u16*)0x4C)

#define OCR1A				*((volatile u16*)0x4A)

#define OCR1B				*((volatile u16*)0x48)

#define ICR1				*((volatile u16*)0x46)

#define TIMSK				*((volatile u8*)0x59)
#define TOIE1		2
#define OCIE1B		3
#define OCIE1A		4
#define TICIE1		5

#define TIFR				*((volatile u8*)0x58)
#define ICF1		5


//Prescaller
#define TIMER1_DIV0		0
#define TIMER1_DIV8		1
#define TIMER1_DIV64	2
#define TIMER1_DIV256	3
#define TIMER1_DIV1028	4
///////////////////////////////////////////////////////////////


//ICU

#define TIMER1_ICU_RISING  1
#define TIMER1_ICU_FALLING 0

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS Prototypes
*******************************************/

void TIMER1_initFastPwmMod14();

void TIMER1_STOP();

void TIMER1_setOcr(u16 value);

//Note: prescaller = 64
void TIMER1_setFrequency(u16 pwm_frequency);

void TIMER1_InitIcu(u8 edge,u8 prescaller);

u16 TIMER1_getICR();

void TIMER1_setcallbackIcu(void (*ptr)());

void TIMER1_setPreload(u16 value);

#endif /* TIMER1_INT_H_ */