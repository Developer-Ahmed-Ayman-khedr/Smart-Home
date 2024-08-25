/*
 * PasswordCheck_PROG.c
 *
 *  Created on: May 18, 2024
 *      Author: Abdo
 */
#include "PasswordCheck_INT.h"

//InitializeEEPROM
u8 EEPROMValues[24];

BOOL EEPROMInitialize(){
	static u16 EEPROMINDEX = 0;
	static BOOL ReturnFlag = FALSE;
	//Read the EEPROM an put it into the EEPROMValues Array
	while (EEPROMINDEX<=MAXEEPROMUSER)
	{
		_delay_ms(50);
		EEPROMValues[EEPROMINDEX] = INTERNALEEPROM_Read(EEPROMINDEX);
		EEPROMINDEX++;
		ReturnFlag = TRUE;
	}
	return ReturnFlag;
}

void password_init ()
{

	DIO_setPinDir(DIO_PINA0,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA2,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA3,DIO_OUTPUT);
}


BOOL CheckPasswordAdmin(){
	static u8 UART_RecevedData = UART_NOT_RECEIVE, Entered_Pass[4], InputIndex = 0, counter=0;
	static BOOL AccessFlag = TRUE;
	//static BOOL ResetFlag = FALSE;
	//static BOOL EneranceFlage = FALSE;


	/*if (ResetFlag==TRUE)
	{
		InputIndex = 0;
		while (InputIndex<4)
		{
			_delay_ms(50);
			INTERNALEEPROM_SendByte(4,InputIndex);
			UART_sendData(InputIndex+48);
			UART_sendStr("\r\n");
			InputIndex++;
		}
		ResetFlag = TRUE;
		InputIndex = 0;
	}*/

	/*if (EneranceFlage==FALSE)
	{
		UART_sendStr("Enter Password\r\n");
		EneranceFlage = TRUE;
	}*/

	UART_RecevedData = UART_receiveData();

	if (UART_RecevedData!=UART_NOT_RECEIVE)
	{
		Entered_Pass[InputIndex] = UART_RecevedData-48;
		UART_sendData(UART_RecevedData);
		UART_sendStr("\r\n");
		InputIndex++;
		UART_RecevedData = UART_NOT_RECEIVE;
	}

	//Try using EEPROMValues Array

	//Check if the user entered 4 Numbers
	if (InputIndex==4)
	{
		InputIndex = 0;
		//Check if the entered Array is equal to the first 4 Elements in the EEPROMValues Array
		while (InputIndex<4)
		{
			if (Entered_Pass[InputIndex]==EEPROMValues[InputIndex])
			{
				AccessFlag = TRUE;
			}
			else
			{
				AccessFlag = FALSE;
				break;
			}
			InputIndex++;
		}
		if (AccessFlag==TRUE)
		{
			UART_sendStr("Welcome\r\n");
			InputIndex=0;
			return TRUE;
		}
		else {
			UART_sendStr("WRONGPASSWORD");
			counter++;
			switch (counter){
				case 1:
				DIO_setPinValue (DIO_PINA0,DIO_HIGH);
				break;
				case 2:
				DIO_setPinValue (DIO_PINA2,DIO_HIGH);
				break;
				case 3:
				DIO_setPinValue (DIO_PINA3,DIO_HIGH);
				UART_sendStr("BLOCK");
				_delay_ms(60000);
				break;
				default:
				break;
			}
		}
		InputIndex = 0;
	}
	return FALSE;
}
