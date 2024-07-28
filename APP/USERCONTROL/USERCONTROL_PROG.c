/*
 * USERCONTROL_PROG.c
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */
#include"USERCONTROL_INT.h"

u8 password[4], username, ch;

u8 array[5];

u8 index ;

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
		EEPROMINDEX+=5;
	}

	if(EEPROMReturnFlag==TRUE){

		for( index = 0;index<=4;index++){

			if(index==0){

					EEPROM_SendByte(array[index],EEPROMINDEX);
					EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
					UART_sendData(EEPROMValue);
					EEPROMINDEX++;
			}

			else if(index>0){

					EEPROM_SendByte(array[index],EEPROMINDEX);
					EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
					UART_sendData(EEPROMValue);
					EEPROMINDEX++;

			}

		}
		index = 0;
	}
}

BOOL CheckDataForUser(){
<<<<<<< HEAD
<<<<<<< HEAD
	u8 KPD_RecevedData , User_Data[5] , Userindex = 0 , EEPROMRecievedData , AccessTimes=1;
	u16 EEPROMIndex =MINEEPROMUSER;
	BOOL AccessResult = FALSE ;
	while (Userindex<=4){
=======
	BOOL flage=FALSE,EEPROM_flage = FALSE,Save_flage = FALSE , flag=0 , Check_index = MINEEPROMUSER + 4;
	u8  KPD_RecevedData, Entered_User[1],Entered_Pass[4], Userindex = 0,Passindex=0, i2 = 0, EEPROMRecevedData,counter=0;

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

>>>>>>> master
=======
	u8 KPD_RecevedData , User_Data[5] , Userindex = 0 , EEPROMRecievedData , AccessTimes=1; 
	u16 EEPROMIndex =MINEEPROMUSER;
	BOOL AccessResult = FALSE ; 
	while (Userindex<=4){
>>>>>>> 89dd561784cd40646aa88ca0df04c0ab8c45c750
	KPD_RecevedData = KPD_read();
	if ( KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
<<<<<<< HEAD
<<<<<<< HEAD
		LCD_sendNum(KPD_RecevedData-48);
		User_Data[Userindex] = KPD_RecevedData;
		Userindex++;
=======

			LCD_sendNum(KPD_RecevedData-48);
			Entered_User[Userindex] = KPD_RecevedData;

			Userindex++;
>>>>>>> master
	}
	}
<<<<<<< HEAD
	while (EEPROMIndex<MAXEEPROMUSER)
=======


	if (Userindex==1&&flag==0)
>>>>>>> master
=======
		LCD_sendNum(KPD_RecevedData-48);
		User_Data[Userindex] = KPD_RecevedData;
		Userindex++;
	}
	}
	while (EEPROMIndex<MAXEEPROMUSER)
>>>>>>> 89dd561784cd40646aa88ca0df04c0ab8c45c750
	{
		_delay_ms(100); 
		EEPROM_ReadByteNACK(&EEPROMRecievedData,EEPROMIndex);
		if (EEPROMRecievedData== User_Data [0])
		{
			for (Userindex=0 ; Userindex<5;Userindex++)
			{
				_delay_ms(50)
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