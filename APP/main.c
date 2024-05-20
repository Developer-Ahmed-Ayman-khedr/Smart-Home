/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "main.h"

int main(){

	u8 Main_Flage=1, read=0;

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
			LCD_sendStr("Enter password:");
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
			LCD_clearDis();
			LCD_Goto(0,0);
			LCD_sendStr("1.Light 2.Temp");
			LCD_Goto(0,1);

			//Go to Keypad read part
			Main_Flage = 5;
			break;
		case 5:
			//Keypad read
			read = KEYPAD_Read();
			if(read==1){
				LCD_sendData('1');
				Main_Flage = 6;
			}
			else if(read==2){
				LCD_sendData('2');
				Main_Flage = 7;
			}
			break;
		case 6:
			//lighting
			break;
		case 7:
			//Temperature check
			LCD_Goto(0,0);
			TEMP_Check();
			LCD_Goto(0,1);
			LCD_sendStr("Return Enter 1:  ");

			//Go to Keypad read part
			Main_Flage = 7;
			break;
		case 8:
			//Keypad read
			read = KEYPAD_Read();
			if(read==1){
				LCD_sendData('1');
				Main_Flage = 3;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
