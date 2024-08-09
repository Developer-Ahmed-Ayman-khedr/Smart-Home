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

BOOL UserLogin(){
	static BOOL AccessResult = FALSE;
	static u8 User_Data[5];
	static u8 KPD_ReceivedData = KPD_UNPRESSED;
	static u8 index = 0;
	static u8 AccessTimes = 0;
	u8 i2 = 4;

	KPD_ReceivedData = KPD_UNPRESSED;
	KPD_ReceivedData = KPD_read();
	if ( KPD_ReceivedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		User_Data[index] = KPD_ReceivedData;
		KPD_ReceivedData = KPD_UNPRESSED;
	}
	//if the user entered five digits
	if (index==5)
	{
		while(i2<24)
		{
			if (User_Data[0]==EEPROMValues[i2])
			{
				index = 0;
				for (u8 index2 = i2; index2<(i2+5); index2++)
				{
					if (User_Data[index]==EEPROMValues[index2])
					{
						AccessResult = TRUE;
					}
					else
					{
						AccessResult = FALSE;
						break;
					}
					index++;
				}

			}
			i2+=5;
		}

		if (AccessResult == TRUE)
		{
			LCD_sendStr("welcome/r/n") ;
			index = 0;
			return AccessResult;
		}
		else{
			switch (AccessTimes)
			{
				AccessTimes++;
				case 1:
					LCD_sendStr("WrongData");
					break;
				case 2 :
					LCD_sendStr("WrongData");
					break;
				case 3 :
					LCD_sendStr("Block") ;
					break;
				default:
				break;
				index = 0;
			}
		}
	}
	return AccessResult;
}

BOOL DeleteUser(u8 userID){
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
