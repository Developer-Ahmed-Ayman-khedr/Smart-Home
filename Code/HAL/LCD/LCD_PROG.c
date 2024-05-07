/*
 * LCD_PROG.c
 *
 * Created: 4/17/2024 6:15:02 PM
 *  Author: ahmed
 */ 

#include "LCD_INT.h"

//Initialize
void LCD_init(){
	DIO_setPinDir(LCD_D4,DIO_OUTPUT);
	DIO_setPinDir(LCD_D5,DIO_OUTPUT);
	DIO_setPinDir(LCD_D6,DIO_OUTPUT);
	DIO_setPinDir(LCD_D7,DIO_OUTPUT);
	
	DIO_setPinDir(LCD_E,DIO_OUTPUT);
	DIO_setPinDir(LCD_RW,DIO_OUTPUT);
	DIO_setPinDir(LCD_RS,DIO_OUTPUT);
	
	LCD_sendCmd(0b00000010);
	_delay_ms(30);
	LCD_sendCmd(0b00101000);
	
	_delay_ms(1);
	LCD_sendCmd(0b00001111);
	
	_delay_ms(1);
	LCD_sendCmd(0b000000001);
	
	_delay_ms(2);
	LCD_sendCmd(0b00000110);
}

//Operation
void LCD_Instruction(u8 type){
	/* 
	RS
	high -> data
	low -> command
	
	RW
	low -> write
	high -> read
	*/

	//Set registers to send data
	if (type==LCD_DATA)
	{
		DIO_setPinValue(LCD_RW,DIO_LOW);
		DIO_setPinValue(LCD_RS,DIO_HIGH);
	}
	
	//Set registers to send command
	else if (type==LCD_CMD)
	{
		DIO_setPinValue(LCD_RW,DIO_LOW);
		DIO_setPinValue(LCD_RS,DIO_LOW);
	}
}

void LCD_pulse(){
	DIO_setPinValue(LCD_E,DIO_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E,DIO_LOW);
}

void LCD_clearDis(){
	LCD_sendCmd(0b00000001);
}

void LCD_GoTo(u8 x, u8 line ){
	if (line==0)
	{
		LCD_sendCmd(0b10000000+x);
	}
	else if (line==1)
	{
		LCD_sendCmd(0b11000000+x);
	}
}

void LCD_CreateNewCharacter(u8* ArrCustumCharachter, u8 CharLocation){
	if (CharLocation<8 && CharLocation>0)
	{
		//Initialize the CGRAM to start taking data
		LCD_sendCmd(0x40+(CharLocation*8));
		
		//Send custom Character to the CGRAM
		u8 i=0;
		while (i<8)
		{
			LCD_sendData(ArrCustumCharachter[i]);
			i++;
		}
		
		//Reset cursor
		LCD_GoTo(0,0);
	}
}

void LCD_Shift(u8 direction){
	if (direction==LCD_SHIFT_DIS_RIGHT)
	{
		//Shift right
		LCD_sendCmd(0b00011100);
	}
	else if (direction==LCD_SHIFT_DIS_LIFT)
	{
		//Shift left
		LCD_sendCmd(0b00011000);
	}
}

//Send
void LCD_sendData(u8 data){
	
	LCD_Instruction(LCD_DATA);
		
	//High bits
	DIO_setPinValue(LCD_D4,GET_BIT(data,4));
	DIO_setPinValue(LCD_D5,GET_BIT(data,5));
	DIO_setPinValue(LCD_D6,GET_BIT(data,6));
	DIO_setPinValue(LCD_D7,GET_BIT(data,7));
	
	LCD_pulse();
	
	//Low bits
	DIO_setPinValue(LCD_D4,GET_BIT(data,0));
	DIO_setPinValue(LCD_D5,GET_BIT(data,1));
	DIO_setPinValue(LCD_D6,GET_BIT(data,2));
	DIO_setPinValue(LCD_D7,GET_BIT(data,3));
	
	LCD_pulse();
	
}

void LCD_sendCmd(u8 cmd){
	
	LCD_Instruction(LCD_CMD);
		
	//High bits
	DIO_setPinValue(LCD_D4,GET_BIT(cmd,4));
	DIO_setPinValue(LCD_D5,GET_BIT(cmd,5));
	DIO_setPinValue(LCD_D6,GET_BIT(cmd,6));
	DIO_setPinValue(LCD_D7,GET_BIT(cmd,7));
	
	LCD_pulse();
	
	//Low bits
	DIO_setPinValue(LCD_D4,GET_BIT(cmd,0));
	DIO_setPinValue(LCD_D5,GET_BIT(cmd,1));
	DIO_setPinValue(LCD_D6,GET_BIT(cmd,2));
	DIO_setPinValue(LCD_D7,GET_BIT(cmd,3));
	
	LCD_pulse();
}

void LCD_sendStr(u8* str){
	u8 i=0;
	while (str[i]!='\0')
	{
		LCD_sendData(str[i]);
		i++;
	}
	
}

void LCD_sendNum(s32 num){
	u8 arr_numbers[10] ;
	s8 i=0;	
	if(num==0){
		LCD_sendData('0');
		return;
	}
	else if (num<0)
	{
		LCD_sendData('-');
	}
	
	while (num>0)
	{
		arr_numbers[i]=(num%10)+48;
		num=num/10;
		i++;
	}
	i--;
	while (i>=0)
	{
		LCD_sendData(arr_numbers[i]);
		i--;
	}
}

void LCD_sendFloatNum(f32 num){
	LCD_sendNum((s32)num);
	
	LCD_sendData('.');
	
	num = num - (u32) num;
	num = num * 1000;
	
	LCD_sendNum((u32)num);
}

void LCD_SendNewCharacter(u8 CharLocation){
	//Show the new character
	LCD_sendData(CharLocation);
}
