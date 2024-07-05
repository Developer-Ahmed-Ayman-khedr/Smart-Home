/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include"Code_APP.h"

<<<<<<< HEAD
void Code_APPInitDriversTask(void *pvParameters){
	while (1)
	{
		//Initialize ADC
		ADC_init();
=======
EventGroupHandle_t LoginEventGroup;


void LoginTask(void * pvParameters )
{
	while(1)
	{
		if(CheckPasswordAdmin()==TRUE){

			xEventGroupSetBits(LoginEventGroup, BIT_0 );
		}
		else if(CheckDataForUser() == TRUE){
			 xEventGroupClearBits( LoginEventGroup, BIT_0 );
		}
	}
}

void Code_APPInitDrivers(){
>>>>>>> Hady_Mohamed_branch

		//Global Interrupt
		GI_enable();

		//Initialize the Keypad
		KPD_init();

		//Initialize the LCD
		LCD_init();

		//Initialize the UART
		UART_init();

		//Initialize the EEPROM
		EEPROM_Init();

		//Initialize the PasswordCheck check process
		password_init ();

		//Initialize the temperature check process
		TEMP_Init();

		//Start the Hold process
		HOLD_init();

		//initialize the Lighting Control process
		LIGHTING_init();

		//initialize the Door Control process
		DOORCONTROL_init();

		vTaskSuspend(NULL);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

QueueHandle_t MyQueue;

void UARTInputTask(void *pvParameters){
	u8 var = UART_NOT_RECEIVE;
	while(1){
		var = UART_receiveData();
		if(var!=UART_NOT_RECEIVE){
			xQueueSend(MyQueue,&var,0);
		}
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

EventBits_t uxBits;

void OptionsTask(void *pvParameters){
	u8 var2, read = 0;
	while(1){
		if (xQueueReceive( MyQueue, &var2, 0) == pdPASS)
		{
			uxBits = xEventGroupWaitBits(xEventGroup, BIT_0, pdTRUE, pdFALSE, 0 );
			if(( uxBits & BIT_0 ) != 1){
				//Correct password Welcome
				UART_sendStr("1.Light 2.Temp 3.Enter\r\n");

				//UART read
				if(UART_receiveData()==INPUT_Light){
					//lighting
					UART_sendStr("1.Hall 2.Entrance\r\n");
					//Go to UART read part for Lighting Section
				}
				else if(UART_receiveData()==INPUT_Temp){
					//Temperature check
					TEMP_Check();
					UART_sendStr("\r\n1 to return:  ");
				}
				else if(UART_receiveData()==INPUT_ENTERANCE){

				}
			}
			else if(){
				LCD_sendStr("1.Light 2.Temp 3.Enter");
				LCD_Goto(0,1);
				//Go to Keypad read part

				//Keypad read
				if(INPUT_Read()==INPUT_Light){
					LCD_sendData('1');
				}
				else if(INPUT_Read()==INPUT_Temp){
					LCD_sendData('2');
				}
				else if(INPUT_Read()==INPUT_ENTERANCE){
					LCD_sendData('3');
				}

				//lighting
				LCD_clearDis();
				LCD_Goto(0,0);
				LCD_sendStr("1.Hall 2.Entrance");
				LCD_Goto(0,1);
				//Go to Keypad read part

				//Keypad read
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_LIGHTINGROOM);
					LIGHTING_Start(LIGHTINGROOM);
				}
				else if(INPUT_Read()=='2'){
					LCD_sendData(INPUT_LIGHTINHALL);
					LIGHTING_Start(LIGHTINHALL);
				}

				//Temperature check
				LCD_Goto(0,0);
				TEMP_Check();
				LCD_Goto(0,1);
				LCD_sendStr("1 to return:  ");
				//Go to Keypad read part

				//Keypad read
				read = INPUT_Read();
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_return);

				}
			}
		}
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

/*void Code_APP(){
	static u8 Admin_Main_Flage=0, User_Main_Flage = 0, read=0;
	if(CheckPasswordAdmin()==TRUE){
		Admin_Main_Flage = 1;
	}
	switch(Admin_Main_Flage){
		case 1:
			//Correct passwordWelcome
			UART_sendStr("1.Light 2.Temp 3.Enter\r\n");
			Admin_Main_Flage = 2;
			break;
		case 2:
			//UART read
			if(UART_receiveData()=='1'){
				//lighting
				UART_sendStr("1.Hall 2.Entrance\r\n");
				//Go to UART read part for Lighting Section
				Admin_Main_Flage = 3;
			}
			else if(UART_receiveData()=='2'){
				//Temperature check
				TEMP_Check();
				UART_sendStr("\r\n1 to return:  ");
				Admin_Main_Flage = 4;
			}
			else if(UART_receiveData()==INPUT_ENTER){
				DOORCONTROL_Start();
				Admin_Main_Flage = 1;
			}
			break;
		case 3:
			//UART read for Lighting Section
			if(UART_receiveData()==LIGHTINGROOM){
				LIGHTING_Start(LIGHTINGROOM);
				Admin_Main_Flage = 1;
			}
			else if(UART_receiveData()==LIGHTINHALL){
				LIGHTING_Start(LIGHTINHALL);
				Admin_Main_Flage = 1;
			}
			break;
		case 4:
			//UART read
			if(UART_receiveData()==RETURN){
				Admin_Main_Flage = 2;
			}
			break;
		default:
			break;
		}

	//User Login
	switch(User_Main_Flage){
		case 1:
			//Hold function
			HOLD_Start();
			LCD_sendNum(HOLD_Retrun());
			LCD_clearDis();
			if(HOLD_Retrun()<=30){
				User_Main_Flage = 2;
			}
			break;
		case 2:
			//Password input
			LCD_sendStr("Enter password:");
			LCD_Goto(0,1);

			//Go to password check part.
			User_Main_Flage = 3;
			break;
		case 3:
			if(CheckDataForUser()==TRUE)
			{
				User_Main_Flage = 4;
			}
			break;
		case 4:
			//Correct passwordWelcome
			LCD_clearDis();
			LCD_Goto(0,0);
			LCD_sendStr("1.Light 2.Temp 3.Enter");
			LCD_Goto(0,1);
			//Go to Keypad read part
			User_Main_Flage = 5;
			break;
		case 5:
			//Keypad read
			if(INPUT_Read()==INPUT_Light){
				LCD_sendData('1');
				User_Main_Flage = 6;
			}
			else if(INPUT_Read()==INPUT_Temp){
				LCD_sendData('2');
				User_Main_Flage = 8;
			}
			else if(INPUT_Read()==INPUT_ENTER){
				LCD_sendData('3');
				User_Main_Flage = 10;
			}
			break;
		case 6:
			//lighting
			LCD_clearDis();
			LCD_Goto(0,0);
			LCD_sendStr("1.Hall 2.Entrance");
			LCD_Goto(0,1);
			//Go to Keypad read part
			User_Main_Flage = 7;
			break;
		case 7:
			//Keypad read
			if(INPUT_Read()=='1'){
				LCD_sendData(INPUT_LIGHTINGROOM);
				LIGHTING_Start(LIGHTINGROOM);
				User_Main_Flage = 5;
			}
			else if(INPUT_Read()=='2'){
				LCD_sendData(INPUT_LIGHTINHALL);
				LIGHTING_Start(LIGHTINHALL);
				User_Main_Flage = 5;
			}
			break;
		case 8:
			//Temperature check
			LCD_Goto(0,0);
			TEMP_Check();
			LCD_Goto(0,1);
			LCD_sendStr("1 to return:  ");
			//Go to Keypad read part
			User_Main_Flage = 9;
			break;
		case 9:
			//Keypad read
			read = INPUT_Read();
			if(INPUT_Read()=='1'){
				LCD_sendData(INPUT_return);
				User_Main_Flage = 4;
			}
			break;
		default:
			break;
		}
}
*/
