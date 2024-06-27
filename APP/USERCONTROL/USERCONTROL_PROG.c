/*
 * USERCONTROL_PROG.c
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */
#include"USERCONTROL_INT.h"

u8 password[4], username[4], ch;

void AddUser()
{
	u8 EEPROMINDEX = MINEEPROMUSER;
	u8 EEPROMValue;
	BOOL EEPROMReturnFlag = FALSE;

	while(EEPROMINDEX<=MAXEEPROMUSER){
		EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
		if(EEPROMValue!=255){
			EEPROMReturnFlag = FALSE;
		}
		else
		{
			EEPROMReturnFlag = TRUE;
			break;
		}
		EEPROMINDEX+=8;
	}
	if(EEPROMReturnFlag==TRUE){
		for(u8 userindex = 0;userindex<=4;userindex++){
			EEPROM_SendByte(username[userindex],EEPROMINDEX);
			EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
			UART_sendData(EEPROMValue);
			EEPROMINDEX++;
		}
		for(u8 passindex = 0;passindex<=4;passindex++){
			EEPROM_SendByte(password[passindex],EEPROMINDEX);
			EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
			UART_sendData(EEPROMValue);
			EEPROMINDEX++;
		}
	}
}

BOOL CheckDataForUser(){
	BOOL flage=FALSE,EEPROM_flage = FALSE,Save_flage = FALSE;
	u8  KPD_RecevedData, Entereduser[4],Entered_Pass[4], i = 0, i2 = 0, EEPROMRecevedData,counter=0;

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

	KPD_RecevedData = KPD_read();
	if ( KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		if (KPD_RecevedData!=KPD_UNPRESSED)
		{
			LCD_sendNum(KPD_RecevedData-48);
			Entered_Pass[i] = KPD_RecevedData;
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
				LCD_sendStr("welcome");
				return TRUE;


			}
			else {
				LCD_sendStr("WRONGPASSWORD");
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

BOOL DeleteUser(){


}
