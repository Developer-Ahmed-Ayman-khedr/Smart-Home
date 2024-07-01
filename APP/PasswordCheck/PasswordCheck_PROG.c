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
	static BOOL flage=FALSE,EEPROM_flage = FALSE,Save_flage = FALSE;
	static u8 UART_RecevedData = 'x', Entered_Pass[4], i = 0, EEPROMRecevedData = 0,counter=0;
	static u16 EEPROMAdminLocation = 0;
	/*while (EEPROMAdminLocation<4)
	{
		_delay_ms(100);
		EEPROM_SendByte(4,EEPROMAdminLocation);
		EEPROMAdminLocation++;
	}*/
	while (EEPROMAdminLocation<4)
	{
		EEPROM_ReadByteNACK(&EEPROMRecevedData,EEPROMAdminLocation);
		_delay_ms(100);
		//UART_sendData(EEPROMRecevedData+48);
		if (EEPROMRecevedData!=255)
		{
			EEPROM_flage = TRUE;
		}
		else
		{
			EEPROM_flage = FALSE;
			break;
		}
		EEPROMAdminLocation++;
	}
	while(i<4){
		//UART_RecevedData = (-48);
		UART_RecevedData = UART_receiveData();
		if (UART_RecevedData!=UART_NOT_RECEIVE)
		{
			//Entered_Pass[i] = UART_receiveData()-48;
			Entered_Pass[i] = UART_RecevedData;
			UART_sendData(Entered_Pass[i]);
			i++;
		}
	}

	if (i==4)
	{
		if (EEPROM_flage==FALSE)
		{
			EEPROMAdminLocation = 0;
			while (EEPROMAdminLocation<4)
			{
				_delay_ms(100);
				EEPROM_SendByte(Entered_Pass[EEPROMAdminLocation],EEPROMAdminLocation);
				EEPROMAdminLocation++;
			}
			Save_flage = TRUE;
		}
		if (EEPROM_flage==TRUE){
			EEPROMAdminLocation = 0;
			while ( EEPROMAdminLocation<4)
			{
				_delay_ms(100);
				EEPROM_ReadByteNACK(&EEPROMRecevedData,EEPROMAdminLocation);
				if (Entered_Pass[EEPROMAdminLocation]==EEPROMRecevedData)
				{
					flage = TRUE;
				}
				else
				{
					flage = FALSE;
					break;
				}
				EEPROMAdminLocation++;
			}
		}

		if (Save_flage==FALSE)
		{
			if (flage==TRUE)
			{
				UART_sendStr("Welcome");
				i=0;
				return TRUE;
			}
			else {
				UART_sendStr("WRONGPASSWORD");
				counter ++ ;
				switch (counter){
				case 1 :
					DIO_setPinValue (DIO_PINA0,DIO_HIGH) ;
					break ;
				case 2 :
					DIO_setPinValue (DIO_PINA2,DIO_HIGH) ;
					break ;
				case 3 :
					DIO_setPinValue (DIO_PINA3,DIO_HIGH) ;
					UART_sendStr("BLOCK");
					_delay_ms(60000);
					break ;
				default:
					break;
				}
			}
		}
		i = 0;
	}
}
