/*
 * UART_PROG.c
 *
 *  Created on: May 26, 2024
 *      Author: ahmed
 */

#include "UART_INT.h"

void UART_init()
{
	//enable T&R
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);

	u8 temp = 0b10000000;
	//disable parity
	CLEAR_BIT(temp,UPM0);
	CLEAR_BIT(temp,UPM1);
	//stop bit
	CLEAR_BIT(temp,USBS);
	//char size
	SET_BIT(temp,UCSZ0);
	SET_BIT(temp,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);

	UCSRC_UBRRH = temp;

	//rate
	UBRRL = 103;
	UCSRC_UBRRH = 0;
}

void UART_sendData(u8 data)
{
	while(GET_BIT(UCSRA,UDRE) == 0);

	UDR = data;
}

void UART_sendStr(u8* str)
{
	u8 i=0;
	while(str[i]!='\0')
	{
		UART_sendData(str[i]);
		i++;
	}
}


u8 UART_receiveData()
{
	u32 timeOut = 100000;
	while(GET_BIT(UCSRA,RXC)==0)
	{
		timeOut--;
		if(timeOut == 0)
		{
			return UART_NOT_RECEIVE;
		}
	}

	return UDR;
}


void UART_INT_init(u8 state)
{
	if (state==UART_ENABLE_RXC)
	{
		//Enable RXC
		SET_BIT(UCSRB,RXCIE);
	}
	else if (state==UART_DISABLE_RXC)
	{
		//Disable RXC
		CLEAR_BIT(UCSRB,RXCIE);
	}
}

//pointer to UART Interrupt function
void (*UART_INTFunc)();

//call back function to send the function from the main function
void UART_setcallbackINT(void (*ptr)()){
	UART_INTFunc = ptr;
}

//Vector Table Function that belongs to UART_INT
//number(in vector table) - 1
void __vector_13() __attribute__((signal));
void __vector_13(){
	UART_INTFunc();
}
