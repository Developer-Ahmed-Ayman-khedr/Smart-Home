/*
 * USERCONTROL_PROG.c
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */
#include"USERCONTROL_INT.h"

void AddUser()
{
	 static u8 userData[5];
	 static u8 EEPROMINDEX = MINEEPROMUSER;
	 static u8 EEPROMValue;
	 static BOOL EEPROMReturnFlag = FALSE;
	 static u8 userindex = 0;
	 static u8 UARTResevedData = UART_NOT_RECEIVE;
	 UART_sendStr("Enter user data:\r\n");
	 while (userindex<=4)
	 {
		 UARTResevedData = UART_NOT_RECEIVE;
		 UARTResevedData = UART_receiveData()-48;
		 if (UARTResevedData!=UART_NOT_RECEIVE)
		 {
			 userData[userindex] = UARTResevedData;
			 userindex++;
			 UARTResevedData = UART_NOT_RECEIVE;
		 }
	 }
	 if (userindex==4)
	 {
		 while(EEPROMINDEX<MAXEEPROMUSER){
			 _delay_ms(100);
			 EEPROMValue = INTERNALEEPROM_Read(EEPROMINDEX);
			 if(EEPROMValue==255){
				 EEPROMReturnFlag = TRUE;
				 break;
			 }
			 else
			 {
				 EEPROMReturnFlag = FALSE;
			 }
			 EEPROMINDEX+=5;
		 }
		 if(EEPROMReturnFlag==TRUE){
			 for(userindex = 0;userindex<=4;userindex++){
				 _delay_ms(50);
				 INTERNALEEPROM_SendByte(userData[userindex],EEPROMINDEX);
				 _delay_ms(50);
				 EEPROMValue = INTERNALEEPROM_Read(EEPROMINDEX);
				 UART_sendData(EEPROMValue);
				 EEPROMINDEX++;
			 }
		 }
  }
}

BOOL CheckDataForUser(){
	static u8 KPD_RecevedData = KPD_UNPRESSED , User_Data[5] , Userindex = 0 , EEPROMRecievedData , AccessTimes=1;
	static u16 EEPROMIndex =MINEEPROMUSER;
	static BOOL AccessResult = FALSE ;
	KPD_RecevedData = KPD_UNPRESSED;
	KPD_RecevedData = KPD_read();
	if ( KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		LCD_sendNum(KPD_RecevedData-48);
		User_Data[Userindex] = KPD_RecevedData;
		Userindex++;
		KPD_RecevedData = KPD_UNPRESSED;
	}
	if (Userindex==4)
	{
		while (EEPROMIndex<MAXEEPROMUSER)
		{
			_delay_ms(100);
			EEPROMRecievedData = INTERNALEEPROM_Read(EEPROMIndex);
			if (EEPROMRecievedData== User_Data [0])
			{
				for (Userindex=0 ; Userindex<5;Userindex++)
				{
					_delay_ms(50);
					EEPROMRecievedData = INTERNALEEPROM_Read(EEPROMIndex) ;
					if (EEPROMRecievedData == User_Data[Userindex])
					{
						AccessResult = TRUE ;
					}
					else
					{
						AccessResult = FALSE ;
						break ;
					}
					EEPROMIndex++;
				}
			}
			EEPROMIndex+=5;
		}

		if (AccessResult == TRUE)
		{
			LCD_sendStr("welcome/r/n") ;
			return TRUE;
		}
		else
		{
			switch (AccessTimes)
			{
				case 1:
				LCD_sendStr("WrongData") ;
				EEPROMIndex = MINEEPROMUSER ;
				break;
				case 2 :
				LCD_sendStr("WrongData") ;
				EEPROMIndex = MINEEPROMUSER ;
				break;
				case 3 :
				LCD_sendStr("Block") ;
				EEPROMIndex = MAXEEPROMUSER ;
				break;
				default:
				break;
			}
			Userindex = 0 ;
			AccessTimes ++ ;
		}
	}
	return FALSE;
}

BOOL DeleteUser(){
	// define flag to delete user
	u8 deleteuserflag = FALSE , i2 = 4 , EEPROMRecievedData ;
	while (i2<21)
	{
		_delay_ms(100);
		EEPROMRecievedData = INTERNALEEPROM_Read(i2);
		if (EEPROMRecievedData == userID)
		{
			deleteuserflag = TRUE;
			for (u8 i=i2;i<(i2+5);i++){
				INTERNALEEPROM_SendByte(0xff,i);
			}
			return TRUE;
		}
		else
		{
			deleteuserflag = FALSE;
		}
		i2+=4;

	}
	return FALSE;
}
