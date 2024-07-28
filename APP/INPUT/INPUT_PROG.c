/*
 * KEYPAD_PROG.c
 *
 *  Created on: May 19, 2024
 *      Author: ahmed
 */
#include "INPUT_INT.h"

u8 INPUT_Read(){
	static u8 Keypad_Press_KPD,UART_Press;
	Keypad_Press_KPD=KPD_read();
	UART_Press=UART_receiveData();
	if (Keypad_Press_KPD!=KPD_UNPRESSED)
	{
		while (KPD_read()!=KPD_UNPRESSED);
		return Keypad_Press_KPD;
	}
	if (UART_Press!=UART_NOT_RECEIVE)
	{
		while (UART_receiveData()!=UART_NOT_RECEIVE);
		return UART_Press;
	}
	return UART_NOT_RECEIVE;
}
