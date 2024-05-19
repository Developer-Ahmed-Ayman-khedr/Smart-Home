/*
 * KEYPAD_PROG.c
 *
 *  Created on: May 19, 2024
 *      Author: ahmed
 */
#include "KEYPAD_INT.h"


void KEYPAD_Init(){
	KPD_init();
	LCD_init();
}



u8 KEYPAD_Read(){
	static u8 Keypad_Press;
	Keypad_Press=KPD_read();
	if (Keypad_Press!= KPD_UNPRESSED)
	{
		while (KPD_read()!= KPD_UNPRESSED);
		return Keypad_Press;
	}
}
