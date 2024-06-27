/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include"Code_APP.h"

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

void Code_APP(){
	static u8 Main_Flage=1, read=0;

	switch(Main_Flage){
			case 1:
				//Hold function
				HOLD_Start();

				LCD_sendNum(HOLD_Retrun());
				LCD_clearDis();

				if(HOLD_Retrun()<=30){
					Main_Flage = 2;
				}
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
				LCD_sendStr("1.Light 2.Temp 3.Enter");
				LCD_Goto(0,1);

				//Go to Keypad read part
				Main_Flage = 5;
				break;
			case 5:
				//Keypad read
				read = INPUT_Read();
				if(read==INPUT_Light){
					LCD_sendData('1');
					Main_Flage = 6;
				}
				else if(read==INPUT_Temp){
					LCD_sendData('2');
					Main_Flage = 8;
				}
				else if(read==INPUT_ENTER){
					LCD_sendData('3');
					Main_Flage = 10;
				}
				break;
			case 6:
				//lighting
				LCD_clearDis();
				LCD_Goto(0,0);
				LCD_sendStr("1.Hall 2.Entrance");
				LCD_Goto(0,1);

				//Go to Keypad read part
				Main_Flage = 7;
				break;
			case 7:
				//Keypad read
				read = INPUT_Read();
				if(read=='1'){
					LCD_sendData(INPUT_LIGHTINGROOM);
					LIGHTING_Start(LIGHTINGROOM);
					Main_Flage = 5;
				}
				else if(read=='2'){
					LCD_sendData(INPUT_LIGHTINHALL);
					LIGHTING_Start(LIGHTINHALL);
					Main_Flage = 5;
				}
				break;
			case 8:
				//Temperature check
				LCD_Goto(0,0);
				TEMP_Check();
				LCD_Goto(0,1);
				LCD_sendStr("1 to return:  ");

				//Go to Keypad read part
				Main_Flage = 9;
				break;
			case 9:
				//Keypad read
				read = INPUT_Read();
				if(read=='1'){
					LCD_sendData(INPUT_return);
					Main_Flage = 4;
				}
				break;
			case 10:
				//Door control function
				DOORCONTROL_Start(&Main_Flage);

				Main_Flage = 1;
				break;
			default:
				break;
			}
}
