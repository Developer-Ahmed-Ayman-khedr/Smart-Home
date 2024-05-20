/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "main.h"

int main(){

	u8 Main_Flage=1;

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

			//Go to password check part.
			Main_Flage = 3;
			break;
		case 3:
			//Password check function
			CheckPassword(&Main_Flage);

			break;
		case 4:
			//Correct passwordWelcome
			LCD_sendStr("1. Lighting:");
			LCD_Goto(0,1);
			LCD_sendStr("2. Temperature check:");

			//Go to Keypad read part
			Main_Flage = 5;
			break;
		case 5:
			//Keypad read
			if(KEYPAD_Read()==1){
				Main_Flage = 6;
			}
			else if(KEYPAD_Read()==2){
				Main_Flage = 7;
			}
			break;
		case 6:
			//lighting
			break;
		case 7:
			//Temperature check
			TEMP_Check();
			LCD_Goto(0,1);
			LCD_sendStr("Enter 1 to return:  ");

			//Go to Keypad read part
			Main_Flage = 7;
			break;
		case 8:
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
