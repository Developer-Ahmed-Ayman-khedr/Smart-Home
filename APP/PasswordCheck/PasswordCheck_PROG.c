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

/*while(ptr!=NULL){
	for (u8 n = 0;n<4;n++){
    if(ptr.start_user==username[c+n]){
        if(ptr.start_pass==password[c+n]){

        }
    }
	}
    ptr=pUser->next;
}*/


u8 c = 4 ;
u8 username[4],password[4];

/*for(u8 k=0;k<3;k++){
		for(u8 k2 = 0 ; k2<4;k2++){
		UART_receiveData(username[k2]);
		EEPROM_SendByte(username[k2],c+k2-48);
		UART_receiveData(password[k2]);
		EEPROM_SendByte(password[k2],c + 4 + k2-48);
		}
		c = c +8;

}*/

u8 create_user(){
	static u16 currentAddress = 4;

	NODE* current = Head , *newnode ;

	newnode=(NODE *)malloc(1*sizeof(NODE));

	newnode->start_address_user = currentAddress;
	newnode->end_address_user = newnode->start_address_user+3;
	newnode->start_address_pass = newnode->end_address_user+1;
	newnode->end_address_pass = newnode->start_address_pass+3;
	newnode->next = NULL;


	UART_sendStr("Enter User ID:");

	u8 Input[8];
	u8 index = 0;
	for( index = newnode->start_address_user ;index < newnode->end_address_pass; index++){

		UART_receiveData(Input[index]);
		if(index==newnode->end_address_user){
			UART_sendStr("Add Password:");
		}
	}

	for(index = newnode->start_address_user ;index < newnode->end_address_pass; index++){}

	if(Head==NULL)
	{
			Head=newnode;
	}
	else
	{
		//newnode->start_address_user = username[4];
		while (current->next!=NULL)
		{
			current=current->next;
		}
		current->next=newnode;
		newnode->next=NULL;
	}



	//current->next=NULL;
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
