/*
 * PasswordCheck_PROG.c
 *
 *  Created on: May 18, 2024
 *      Author: Abdo
 */
#include "PasswordCheck_INT.h"




void password_init (){

	DIO_setPinDir(DIO_PINA0,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA2,DIO_OUTPUT) ;

	//DIO_setPinDir (DIO_PINA3,DIO_OUTPUT) ;

	DIO_setPinDir (DIO_PINA3,DIO_OUTPUT) ;
}


u8 enteredPassword [4];
u8 SavedPassword [4] = {'4','4','4','4'} ;
u8 key=0 ;
u8 i = 0 ;
BOOL flage = FALSE ;
u8 counter = 0 ;

void CheckPassword (u8* Ma_Fl_ptr){
	key=KPD_read();
	if (key!= KPD_UNPRESSED)
	{

		enteredPassword [i]=key ;
		 LCD_sendData (key);
			i++ ;
		while (KPD_read()!= KPD_UNPRESSED);

	}
	if (i==4){

		u8 k ;
		for (k=0 ;k<4;k++)
		{
			if (enteredPassword [k] ==SavedPassword [k] )
			{
				flage = TRUE ;
			}
			else
			{
				flage = FALSE ;
				break ;
			}
		}

		i = 0 ;
		if (flage==TRUE)
		{
			LCD_sendStr("welcome");
			* Ma_Fl_ptr = 4 ;


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
				//DIO_setPinValue (DIO_PINA3,DIO_HIGH) ;
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









}
