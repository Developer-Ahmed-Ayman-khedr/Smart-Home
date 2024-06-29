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
	static u8 UART_RecevedData = 0, Entered_Pass[4], i = 0, EEPROMRecevedData = 0,counter=0;
	static u16 i2 = 0;
	/*while (i2<4)
	{
		_delay_ms(100);
		EEPROM_SendByte(4,i2);
		i2++;
	}*/
	while (i2<4)
	{
		EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
		_delay_ms(100);
		//UART_sendData(EEPROMRecevedData+48);
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
	UART_RecevedData = (UART_receiveData()-48);
	UART_sendData(UART_RecevedData+48);
	if (UART_RecevedData!=UART_NOT_RECEIVE)
	{
		Entered_Pass[i] = UART_RecevedData;
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
