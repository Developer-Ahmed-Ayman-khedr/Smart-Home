/*
 * LCD_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: Abdo
 */


#include "LCD_INT.h"

void LCD_pulse ()
{
	DIO_setPinValue(LCD_E, DIO_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E, DIO_LOW);
}

void LCD_init ()
{
	DIO_setPinDir(LCD_D4, DIO_OUTPUT);
	DIO_setPinDir(LCD_D5, DIO_OUTPUT);
	DIO_setPinDir(LCD_D6, DIO_OUTPUT);
	DIO_setPinDir(LCD_D7, DIO_OUTPUT);

	DIO_setPinDir(LCD_RS, DIO_OUTPUT);
	DIO_setPinDir(LCD_RW, DIO_OUTPUT);
	DIO_setPinDir(LCD_E, DIO_OUTPUT);

	_delay_ms(30);
	LCD_sendcmd(0b00000010);
	LCD_sendcmd(0b00101000);
	_delay_ms(1);
	LCD_sendcmd(0b00001111);
	_delay_ms(1);
	LCD_sendcmd(0b00000001);
	_delay_ms(2);
	LCD_sendcmd(0b00000110);


}
void LCD_sendData(u8 data)
{
	DIO_setPinValue(LCD_RW, DIO_LOW);
	DIO_setPinValue(LCD_RS,DIO_HIGH);

	DIO_setPinValue(LCD_D4, GET_BIT(data,4));
	DIO_setPinValue(LCD_D5, GET_BIT(data,5));
	DIO_setPinValue(LCD_D6, GET_BIT(data,6));
	DIO_setPinValue(LCD_D7, GET_BIT(data,7));
	LCD_pulse();
	/////////////////////////////////////////////
	DIO_setPinValue(LCD_D4, GET_BIT(data,0));
	DIO_setPinValue(LCD_D5, GET_BIT(data,1));
	DIO_setPinValue(LCD_D6, GET_BIT(data,2));
	DIO_setPinValue(LCD_D7, GET_BIT(data,3));
	LCD_pulse();

}
void LCD_sendcmd (u8 cmd)
{
	DIO_setPinValue(LCD_RW, DIO_LOW);
	DIO_setPinValue(LCD_RS,DIO_LOW);

	DIO_setPinValue(LCD_D4, GET_BIT(cmd,4));
	DIO_setPinValue(LCD_D5, GET_BIT(cmd,5));
	DIO_setPinValue(LCD_D6, GET_BIT(cmd,6));
	DIO_setPinValue(LCD_D7, GET_BIT(cmd,7));
	LCD_pulse();
	/////////////////////////////////////////////
	DIO_setPinValue(LCD_D4, GET_BIT(cmd,0));
	DIO_setPinValue(LCD_D5, GET_BIT(cmd,1));
	DIO_setPinValue(LCD_D6, GET_BIT(cmd,2));
	DIO_setPinValue(LCD_D7, GET_BIT(cmd,3));
	LCD_pulse();
}

void LCD_clearDis()
{
	LCD_sendcmd(0b00000001);
}

void LCD_sendStr (u8*str)
{
	u8 i=0;
	while(str[i]!='\0')
	{
		LCD_sendData(str[i]);
		i++;
	}

}


void LCD_sendNum (s32 num)
{
	u8 arr[10];
	s8 counter =0 ;
	if (num==0)
	{
		LCD_sendData(0);
		 /////break ;
	}
	if (num<0)
	{
		LCD_sendData('-');
	}
	while (num>0)
	{
		arr[counter]=((num%10)+48);
		num=num/10;
		counter ++ ;

	}
	counter -- ; // ???
	while (counter >=0)
	{

		LCD_sendData(arr[counter]);
		counter -- ;
	}
}
void LCD_sendFloatNum(f32 num)
{
	LCD_sendNum((s32)num);

	LCD_sendData('.');
	f32 no = num - (s32) num ;
	no = no * 1000 ;
	LCD_sendNum((s32)no);
}

void LCD_Goto (u8 x , u8 line )
{
	if (line == 0)
	{
	LCD_sendcmd (0b10000000+x);	// IF YOU GO TO ABOVE LINE
	}
	else if (line==1)
	{
		LCD_sendcmd(0b11000000+x);
	}
}

