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

		_delay_ms(100);
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
	u8 KPD_RecevedData , User_Data[5] , Userindex = 0 , EEPROMRecievedData , AccessTimes=1;
	u16 EEPROMIndex =MINEEPROMUSER;
	BOOL AccessResult = FALSE ;
	while (Userindex<=4){
	KPD_RecevedData = KPD_read();
	if ( KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		LCD_sendNum(KPD_RecevedData-48);
		User_Data[Userindex] = KPD_RecevedData;
		Userindex++;
	}
	}
	while (EEPROMIndex<MAXEEPROMUSER)
	{
		_delay_ms(100);
		EEPROM_ReadByteNACK(&EEPROMRecievedData,EEPROMIndex);
		if (EEPROMRecievedData== User_Data [0])
		{
			for (Userindex=0 ; Userindex<5;Userindex++)
			{
				_delay_ms(50);
				EEPROM_ReadByteNACK(&EEPROMRecievedData , EEPROMIndex) ;
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

BOOL DeleteUser(u8 userID){

	// define flag to delete user
	 u8 deleteuserflag = FALSE , i2 = 4 , EEPROMRecievedData ;
		 while (i2<21)
		 	{
		 		_delay_ms(100);
		 		EEPROM_ReadByteNACK(&EEPROMRecievedData,i2);
		 		if (EEPROMRecievedData == userID)
		 		{
		 			deleteuserflag = TRUE;
		 			for (u8 i=i2;i<(i2+5);i++){
		 				EEPROM_SendByte(0xff,i);
		 			}
		 		}
		 		else
		 		{
		 			deleteuserflag = FALSE;
		 		}
		 		i2+=4;

		 	}

}







