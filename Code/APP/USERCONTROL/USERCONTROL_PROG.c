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
	u8 KPD_ReceivedData = KPD_UNPRESSED;
	static u8 index = 0;
	static u8 counter = 0;

	AccessResult = FALSE;

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
		u8 i2 = 4;
		while(i2<24)
		{

			//Check if the first digit is equal to a place in the EEPROMValues array in the addresses (4,9,14,19)
			if (User_Data[0]==EEPROMValues[i2])
			{
				index = 0;
				for (u16 index2 = i2; index2<(i2+5); index2++)
				{
					if (User_Data[index]==EEPROMValues[index2])
					{
						//LCD_sendData('w');
						AccessResult = TRUE;
					}
					else
					{
						AccessResult = FALSE;
						break;
					}
					index++;
				}
				break;
			}
			else{
				AccessResult = FALSE;
			}
			i2+=5;
		}

		LCD_clearDis();
		if (AccessResult==TRUE)
		{
			LCD_sendStr("Welcome");
			index = 0;
			_delay_ms(300);
			return AccessResult;
		}
		else{
			LCD_sendStr("WrongData");
			counter++;
			switch (counter){
				case 1:
				DIO_setPinValue (DIO_PINA0,DIO_HIGH);
				break;
				case 2:
				DIO_setPinValue (DIO_PINA2,DIO_HIGH);
				break;
				case 3:
				DIO_setPinValue (DIO_PINA3,DIO_HIGH);
				LCD_sendStr("BLOCK");
				_delay_ms(60000);
				break;
				default:
				break;
			}
		}
		index = 0;

	}
	return AccessResult;
}

void DeleteUser(u8 userID){
	switch (userID)
	{
		case 1:
			for (u8 i = 4; i<9; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		case 2:
			for
			(u8 i = 9; i<14; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		case 3:
			for (u8 i =14 ; i<19; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		case 4:
			for (u8 i = 19; i<=24; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		default:
			break;
	}
	UART_sendStr("Deleted\r\n");
	EEPROMInitialize();
}
