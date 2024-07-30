/*
 * USERCONTROL_PROG.c
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */
#include"USERCONTROL_INT.h"++

u8 password[4], username;

u8 array[5];

u8 index ;

void AddUser()
{
 u8 userData[5];
 u8 EEPROMINDEX = MINEEPROMUSER;
 u8 EEPROMValue;
 BOOL EEPROMReturnFlag = FALSE;
 u8 userindex = 0;
 u8 UARTResevedData = UART_NOT_RECEIVE;
 while(EEPROMINDEX<MAXEEPROMUSER){
  _delay_ms(100);
  EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
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
 while (userindex<=4)
 {
  UARTResevedData = UART_receiveData();
  if (UARTResevedData!=UART_NOT_RECEIVE)
  {
   userData[userindex] = UARTResevedData;
   userindex++;
  }
 }
 if(EEPROMReturnFlag==TRUE){
  for(userindex = 0;userindex<=4;userindex++){
   _delay_ms(50);
   EEPROM_SendByte(userData[userindex],EEPROMINDEX);
   _delay_ms(50);
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

BOOL DeleteUser(){

	// define flag to delete user
	 u8 deleteuserflag = FALSE , i2 = 0 , EEPROMRecevedData ;
		 while (i2<4)
		 	{
		 		_delay_ms(100);
		 		EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
		 		if (EEPROMRecevedData!=255)
		 		{
		 			deleteuserflag = TRUE;
		 		}
		 		else
		 		{
		 			deleteuserflag = FALSE;
		 		}
		 		i2++;

		 	}


}
