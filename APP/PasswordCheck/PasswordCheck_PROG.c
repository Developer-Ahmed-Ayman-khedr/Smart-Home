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

	DIO_setPinDir (DIO_PINA2,DIO_OUTPUT) ;

	//DIO_setPinDir (DIO_PINA3,DIO_OUTPUT) ;

	DIO_setPinDir (DIO_PINA3,DIO_OUTPUT) ;
}

BOOL CheckPasswordAdmin(){
	u8 c = 4 ;
	u8 username[4],password[4];
	BOOL flage=FALSE,EEPROM_flage = FALSE,Save_flage = FALSE;
	u8 UART_RecevedData, Entered_Pass[4], i = 0, i2 = 0, EEPROMRecevedData,counter=0;
	while (i2<4)
	{
		_delay_ms(100);
		EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
		if (EEPROMRecevedData!=255)
		{
			EEPROM_flage = TRUE;
		}
		else
		{
			EEPROM_flage = FALSE;
		}
		i2++;
	}

	UART_RecevedData = UART_receiveData();
	if (UART_RecevedData!=UART_NOT_RECEIVE)
	{
		if (UART_RecevedData!=UART_NOT_RECEIVE)
		{
			Entered_Pass[i] = UART_RecevedData;
		}
		i++;
	}

	if (i==4)
	{
		if (EEPROM_flage==FALSE)
		{
			i2 = 0;
			while (i2<4)
			{
				_delay_ms(100);
				EEPROM_SendByte(Entered_Pass[i2],i2);
				i2++;
			}
			Save_flage = TRUE;
		}
		if (EEPROM_flage==TRUE){
			i2 = 0;
			while ( i2<4)
			{
				_delay_ms(100);
				EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
				if (Entered_Pass[i2]==EEPROMRecevedData)
				{
					flage = TRUE;
				}
				else
				{
					flage = FALSE;
					break;
				}
				i2++;
			}
		}

		if (Save_flage==FALSE)
		{
			if (flage==TRUE)
			{
				UART_sendStr("welcome");
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
