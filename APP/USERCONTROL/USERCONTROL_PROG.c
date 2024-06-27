/*
 * USERCONTROL_PROG.c
 *
 *  Created on: Jun 25, 2024
 *      Author: DELL
 */
#include"USERCONTROL_INT.h"

u8 password[4], username[4], ch;

void AddUserName(){
	u32 i = MINEEPROMUSER;
	u8 EEPROMValue;
	BOOL EEPROMReturnFlag = FALSE;

	while(i<=MAXEEPROMUSER){
		EEPROM_ReadByteNACK(&EEPROMValue,i);
		if(EEPROMValue!=255){
			EEPROMReturnFlag = FALSE;
		}
		else
		{
			EEPROMReturnFlag = TRUE;
			break;
		}
		i+=4;
	}
	if(EEPROMReturnFlag==TRUE){
		for(u8 arrayindex = 0;arrayindex<=4;arrayindex++){

			EEPROM_SendByte(username[arrayindex],i);
			i++;
			EEPROM_ReadByteNACK(&EEPROMValue,i);
			UART_sendData(EEPROMValue);
		}
	}
}

void AddPassword()
{
	u8 k = MINEEPROMPASS ;
	u8 EEPROMValue;
	BOOL EEPROMReturnFlag = FALSE;
	while(k<=MAXEEPROMPASS){
		EEPROM_ReadByteNACK(&EEPROMValue,k);
		if(EEPROMValue!=255){
			EEPROMReturnFlag = FALSE;
		}
		else {
			EEPROMReturnFlag = TRUE;
			break;
		}
		k+=4;
	}
	if(EEPROMReturnFlag==TRUE){
		for(u8 arrayindex = 0;arrayindex<=4;arrayindex++){
			EEPROM_SendByte(password[arrayindex],k);
			k++;
			EEPROM_ReadByteNACK(&EEPROMValue,i);
			UART_sendData(EEPROMValue);
		}
	}
}

u8 DeleteUser(){


}
