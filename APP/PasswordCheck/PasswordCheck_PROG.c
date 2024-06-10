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

	EEPROM_Init();
}



BOOL flage=FALSE,EEPROM_flage = FALSE,Save_flage = FALSE;
u8 UART_RecevedData, KPD_RecevedData, Entered_Pass[4], i = 0, i2 = 0, EEPROMRecevedData,counter=0;


void CheckPassword (u8* Ma_Fl_ptr){
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
	KPD_RecevedData = KPD_read();
	if (UART_RecevedData!=UART_NOT_RECEIVE || KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		if (KPD_RecevedData!=KPD_UNPRESSED)
		{
			LCD_sendNum(KPD_RecevedData-48);
			Entered_Pass[i] = KPD_RecevedData;
		}
		else if (UART_RecevedData!=UART_NOT_RECEIVE)
		{
			LCD_sendNum(UART_RecevedData-48);
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
				}
				i2++;
			}
		}

		if (Save_flage==FALSE)
		{
			if (flage==TRUE)
			{
				LCD_sendStr("welcome");
				UART_sendStr("welcome");
				* Ma_Fl_ptr = 5 ;


			}
			else {
				LCD_sendStr("WRONGPASSWORD");
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
					LCD_clearDis();
					LCD_sendStr("BLOCK");
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
