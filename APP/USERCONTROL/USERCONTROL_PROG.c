/*
 * USERCONTROL_PROG.c
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */
#include"USERCONTROL_INT.h"

extern u8 EEPROMValues[24];

void AddUser(){
	 // temp array to put pass in the main array
	 u8 TEMPArr [5] ;
	 u8 UARTResevedData = UART_NOT_RECEIVE;

	 UART_sendStr("Enter pass:\r\n");
	 u8 index1 = 0;
	 while (index1<5)
	 {
		 UARTResevedData = UART_NOT_RECEIVE;
		 UARTResevedData = UART_receiveData();
		 if (UARTResevedData!=UART_NOT_RECEIVE)
		 {
			 TEMPArr[index1] = UARTResevedData-48;
			 index1++;
			 UARTResevedData = UART_NOT_RECEIVE;
		 }
	 }
	 if (index1==5)
	 {
		 UART_sendStr("Saving\r\n");
		 for (u8 Arrayindex=4 ;Arrayindex<24 ; Arrayindex+=5)
		 {
			 if ( EEPROMValues[Arrayindex] == 255 )
			 {
				 u8 INDEX1 = 0;
				 for (u8 EEPROMIndex= Arrayindex ;EEPROMIndex<(Arrayindex+5) ;EEPROMIndex++)
				 {
					 // will put the pass from temp array in EEPROMValues
					 EEPROMValues [EEPROMIndex] = TEMPArr [INDEX1];
					 INDEX1++;
				 }
				 break;
			 }
		 }

		 for (u16 EEPROMIndex=4 ;EEPROMIndex<=23;EEPROMIndex++)
		 {
			 _delay_ms(50) ;
			 INTERNALEEPROM_SendByte(EEPROMValues[EEPROMIndex],EEPROMIndex);
		 }
	 }
	 EEPROMInitialize();
}

BOOL UserLogin(){
	static BOOL AccessResult = FALSE;
	static u8 User_Data[5];
	static u8 KPD_ReceivedData = KPD_UNPRESSED;
	static u8 index = 0;
	static u8 counter = 0;

	//used to reset the EEPROM that is responsible for the users
	/*static BOOL ResetFlag = FALSE;


	if (ResetFlag==TRUE)
	{
		index = 4;
		while (index<24)
		{
			_delay_ms(50);
			INTERNALEEPROM_SendByte(255,index);
			UART_sendData(index+48);
			UART_sendStr("\r\n");
			index++;
		}
		ResetFlag = TRUE;
		index = 0;
	}*/

	KPD_ReceivedData = KPD_read();
	if (KPD_ReceivedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		LCD_sendData(KPD_ReceivedData);
		User_Data[index] = KPD_ReceivedData-48;
		index++;
	}
	//if the user entered five digits
	if (index>4)
	{
		//LCD_clearDis();
		//LCD_sendStr("Checking");
		//LCD_GoTo(0,1);
		u8 i2 = 4;
		while(i2<24)
		{
			if (User_Data[0]==EEPROMValues[i2])
			{
				//LCD_sendStr("w");
				//LCD_sendNum(EEPROMValues[i2]);
				index = 0;
				for (u16 index2 = i2; index2<(i2+5); index2++)
				{
					if (User_Data[index]==EEPROMValues[index2])
					{
						LCD_sendData('w');
						AccessResult = TRUE;
					}
					else
					{
						//LCD_sendStr("n");
						AccessResult = FALSE;
						break;
					}
					index++;
				}
				break;
			}
			else{
				LCD_sendData('n');
				AccessResult = FALSE;
			}
			i2+=5;
		}

		//LCD_clearDis();
		if (AccessResult==TRUE)
		{
			LCD_sendStr("Welcome");
			index = 0;
			return AccessResult;
		}
		else if (AccessResult==FALSE)
		{
			counter++;
			if (counter==1)
			{
				LCD_sendStr("WrongData");
			}
			else if (counter==2)
			{
				LCD_sendStr("WrongData");
			}
			else if (counter==3)
			{
				LCD_sendStr("Block");
			}
			/*switch (LoginTimes)
			{
				case 0:
					LCD_sendStr("WrongData");
					break;
				case 1:
					LCD_sendStr("WrongData");
					break;
				case 2:
					LCD_sendStr("Block");
					break;
				default:
					break;
			}*/
		}
		index = 0;

	}
	return AccessResult;
}

BOOL DeleteUser(u8 userID){
	switch (userID)
	{
	case 1:
		for (u8 i = 4; i<9; i++){
			INTERNALEEPROM_SendByte(255,i);
		}
		UART_sendStr("Deleted\r\n");
		break;
	case 2:
		for (u8 i = 9; i<13; i++){
			INTERNALEEPROM_SendByte(255,i);
		}
		UART_sendStr("Deleted\r\n");
		break;
		case 3:
		for (u8 i =13 ; i<18; i++){
			INTERNALEEPROM_SendByte(255,i);
		}
		UART_sendStr("Deleted\r\n");
		break;
		case 4:
		for (u8 i = 18; i<=24; i++){
			INTERNALEEPROM_SendByte(255,i);
		}
		UART_sendStr("Deleted\r\n");
		break;

	default:
		break;
	}

}
