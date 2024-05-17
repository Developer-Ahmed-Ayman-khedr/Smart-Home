/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "main.h"

int main(){

	u8 Main_Flage=0, main_password;

	//Start the Hold process
	HOLD_init();

	//Initialize the temperature check process
	TEMP_Init();

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

			//Password input function and wait inside it for input for 1 minute
			//to give the user the time for inputing


			//Password check function

			break;
		case 3:
			//Correct passwordWelcome
			LCD_sendStr("1. Lighting:");
			LCD_Goto(0,1);
			LCD_sendStr("2. Temperature check:");

			//Keypad read and wait for input for 3 seconds
			//Main_Flage = Keypad_read();
			break;
		case 4:
			//lighting
			break;
		case 5:
			//Temperature check
			TEMP_Check();
			LCD_Goto(0,1);
			LCD_sendStr("Enter 3 to return:");

			//Keypad read and wait for input for 3 seconds
			//Main_Flage = Keypad_read();
			break;
		default:
			break;
		}

	}
	return 0;
}
