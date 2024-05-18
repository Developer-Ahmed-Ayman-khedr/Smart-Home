/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "main.h"

int main(){

	u8 Main_Flage=0;

	//Start the Hold process
	HOLD_init();

	//Initialize the temperature check process
	TEMP_Init();

	//Initialize the Keypad input process
	KEYPAD_Init();

	//Initialize the Password Check check process
	password_init ();


	while (1){

		switch(Main_Flage){
		case 1:
			//Hold function
			HOLD_Start(&Main_Flage);
			break;
		case 2:
			//Password input
			LCD_sendStr("Please enter your password:");
			LCD_Goto(0,1);

			//Password check function
			CheckPassword(&Main_Flage);

			break;
		case 3:
			//Correct passwordWelcome
			LCD_sendStr("1. Lighting:");
			LCD_Goto(0,1);
			LCD_sendStr("2. Temperature check:");

			//Keypad read
			if(KEYPAD_Read()==1){
				Main_Flage = 4;
			}
			else if(KEYPAD_Read()==2){
				Main_Flage = 5;
			}
			break;
		case 4:
			//lighting
			break;
		case 5:
			//Temperature check
			TEMP_Check();
			LCD_Goto(0,1);
			LCD_sendStr("Enter 1 to return:  ");

			//Keypad read
			if(KEYPAD_Read()==1){
				Main_Flage = 3;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
