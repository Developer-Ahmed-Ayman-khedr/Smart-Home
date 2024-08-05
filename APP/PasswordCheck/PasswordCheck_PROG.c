/*
 * PasswordCheck_PROG.c
 *
 *  Created on: May 18, 2024
 *      Author: Abdo
 */
#include "PasswordCheck_INT.h"

void password_init ()
{

	DIO_setPinDir(DIO_PINA0,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA2,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA3,DIO_OUTPUT);
}


BOOL CheckPasswordAdmin(){
	static u8 UART_RecevedData = UART_NOT_RECEIVE, Entered_Pass[4], InputIndex = 0, EEPROMRecevedData = 0,counter=0;
	static u16 EEPROMAdminLocation = 0;
	static BOOL AccessFlag = TRUE;
	UART_RecevedData = UART_NOT_RECEIVE;
	UART_RecevedData = UART_receiveData()-48;
	if (UART_RecevedData!=UART_NOT_RECEIVE)
	{
		Entered_Pass[InputIndex] = UART_RecevedData;
		//UART_sendData(UART_RecevedData+48);
		//UART_sendStr("\r\n");
		InputIndex++;
		UART_RecevedData = UART_NOT_RECEIVE;
	}
	if (InputIndex==4)
	{
			InputIndex = 0;
			EEPROMAdminLocation = 0;
			while (EEPROMAdminLocation<4)
			{
				_delay_ms(50);
				EEPROMRecevedData = INTERNALEEPROM_Read(EEPROMAdminLocation);
				if (Entered_Pass[InputIndex]==EEPROMRecevedData)
				{
					AccessFlag = TRUE;
				}
				else
				{
					AccessFlag = FALSE;
					break;
				}
				EEPROMAdminLocation++;
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
