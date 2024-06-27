/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include"Code_APP.h"

BOOL HoldFunc(){
	//Hold function
	HOLD_Start();

	LCD_sendNum(HOLD_Retrun());
	LCD_clearDis();

	if(HOLD_Retrun()<=30){
		return TRUE;
	}
}

BOOL Passwordinputfunc(){
	//Password input
	LCD_sendStr("Enter password:");
	LCD_Goto(0,1);

	//Go to password check part.
	return TRUE;
}

BOOL Passwordcheckfunc(){
	//Password check function
	if(CheckPassword()==TRUE){
		return TRUE;
	}
}
BOOL CorrectpasswordWelcomefunc(){
	//Correct passwordWelcome
	LCD_clearDis();
	LCD_Goto(0,0);
	LCD_sendStr("1.Light 2.Temp 3.Enter");
	LCD_Goto(0,1);
	return TRUE;
}

BOOL lightingfunc(){
	//lighting
	LCD_clearDis();
	LCD_Goto(0,0);
	LCD_sendStr("1.Hall 2.Entrance");
	LCD_Goto(0,1);
	return TRUE;
}

void Code_APPInitDrivers(){
	//Start the Hold process
		HOLD_init();

		//Initialize the temperature check process
		TEMP_Init();

		//Initialize the Keypad input process
		INPUT_Init();

		//Initialize the Password Check check process
		password_init ();

		//initialize the Lighting Control process
		LIGHTING_init();

		//initialize the Door Control process
		DOORCONTROL_init();
}

BOOL Temperaturecheckfunc(){
	//Temperature check
	LCD_Goto(0,0);
	TEMP_Check();
	LCD_Goto(0,1);
	LCD_sendStr("1 to return:  ");
	return TRUE;
}

void Code_APP(){
	static u8 Main_Flage=1, read=0;

	switch(Main_Flage){
			case 1:
				if(HoldFunc()==TRUE){
					Main_Flage = 2;
				}
				break;
			case 2:
				if(Passwordinputfunc()){
					Main_Flage = 3;
				}
				break;
			case 3:
				if(Passwordcheckfunc()==TRUE){
					Main_Flage = 4;
				}
				break;
			case 4:
				if(CorrectpasswordWelcomefunc()==TRUE){
					//Go to Keypad read part
					Main_Flage = 5;
				}
				break;
			case 5:
				//Keypad read
				if(INPUT_Read()==INPUT_Light){
					LCD_sendData('1');
					Main_Flage = 6;
				}
				else if(INPUT_Read()==INPUT_Temp){
					LCD_sendData('2');
					Main_Flage = 8;
				}
				else if(INPUT_Read()==INPUT_ENTER){
					LCD_sendData('3');
					Main_Flage = 10;
				}
				break;
			case 6:
				if(lightingfunc()==TRUE){
					//Go to Keypad read part
					Main_Flage = 7;
				}
				break;
			case 7:
				//Keypad read
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_LIGHTINGROOM);
					LIGHTING_Start(LIGHTINGROOM);
					Main_Flage = 5;
				}
				else if(INPUT_Read()=='2'){
					LCD_sendData(INPUT_LIGHTINHALL);
					LIGHTING_Start(LIGHTINHALL);
					Main_Flage = 5;
				}
				break;
			case 8:
				if(Temperaturecheckfunc()){
					//Go to Keypad read part
					Main_Flage = 9;
				}
				break;
			case 9:
				//Keypad read
				read = INPUT_Read();
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_return);
					Main_Flage = 4;
				}
				break;
			default:
				break;
			}

}
