/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include"Code_APP.h"

extern u8 EEPROMValues[24];

void Code_APPInitDriversTask(void *pvParameters){
	while(1){
		GI_enable();
		KPD_init();
		LCD_init();
		UART_init();
		EEPROMInitialize();

		HOLD_init();
		DOORCONTROL_init();
		vTaskSuspend(NULL);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void LoginTask(void * pvParameters ){
	while(1)
	{
		vTaskSuspend(OptionsTaskHandle);
		if(CheckPasswordAdmin()==TRUE)
		{
			xEventGroupSetBits(LoginEventGroup, BIT_0);

			//xEventGroupClearBits(LoginEventGroup, BIT_1 );

			vTaskResume(OptionsTaskHandle);

			vTaskSuspend(LoginTaskHandle);
		}
		if(UserLogin() == TRUE){

			/*LCD_GoTo(0,0);

			LCD_clearDis();

			LCD_sendData('H');*/

			xEventGroupSetBits(UserEventGroup,BIT_0);


			//xEventGroupSetBits( LoginEventGroup, BIT_1);

			//xEventGroupClearBits(LoginEventGroup, BIT_0);

			vTaskResume(OptionsTaskHandle);

			vTaskSuspend(LoginTaskHandle);
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void OptionsTask(void *pvParameters){
	static u8 ControlCounter = 0;
	EventBits_t uxBits;
	u8 recieve = UART_NOT_RECEIVE;
	while(1){
		uxBits = xEventGroupWaitBits(LoginEventGroup, BIT_0, pdFALSE, pdFALSE, 0 );
		//Admin Section
		if(( uxBits & BIT_0 ) != 0){
			if (ControlCounter==0)
			{
				//Correct password Welcome
				UART_sendStr("1.Light 2.Temp 3.Enter 4.Add User 5.Delete User 6.logout\r\n");
				ControlCounter = 1;
			}
			if (ControlCounter==1)
			{
				//UART read
				recieve = UART_receiveDataWait();

				if(recieve==INPUT_Light){
					//lighting
					UART_sendStr("1.Hall 2.Entrance\r\n");

					recieve = UART_receiveDataWait();

					if (recieve ==LIGHTINGROOM)
					{
						LIGHTING_Start(LIGHTINGROOM);
					}
					else if (recieve == LIGHTINHALL)
					{
						LIGHTING_Start(LIGHTINHALL);
					}
				}
				else if(recieve ==INPUT_Temp){
					//Temperature check
					TEMP_Check(OUTPUTUART);

				}

				else if (recieve ==INPUT_ENTERANCE)
				{
					DOORCONTROL_Start();
					//ControlCounter = 0;
				}

				else if (recieve ==INPUT_ADDUSER)
				{
					//UART_sendStr("\r\n Add user data \r\n");
					//UART_sendStr("Enter user id\r\n");
					AddUser();
					//ControlCounter = 0;
				}
				else if (recieve == INPUT_DELETEUSER)
				{
					// show the saved users for admin to delete from them
					UART_sendStr("\r\n");
					for (u8 i=4 ; i<24 ; i++)
					{
						UART_sendData(EEPROMValues[i]+48);
						if (i==8||i==13||i==18||i==23)
						{
							UART_sendData('*');
						}
					}
					UART_sendStr("\r\nEnter user id\r\n");
					recieve = UART_receiveDataWait()-48;
					DeleteUser(recieve);
					//ControlCounter = 0;
				}
				else if (recieve == INPUT_LOGOUTADMIN)
				{
					xEventGroupClearBits(LoginEventGroup, BIT_0);
				}
				ControlCounter = 0;
			}
		}

		uxBits = xEventGroupWaitBits(UserEventGroup, BIT_0, pdFALSE, pdFALSE, 0 );
		//User Section
		if(( uxBits & BIT_0 ) != 0){

			LCD_sendData('H');

			if (ControlCounter==0)
			{
				LCD_sendData('H');
				//Correct password Welcome
				u8 lcdsend1[15] = "1.Light 2.Temp";
				LCD_sendStr(lcdsend1[0]);
				LCD_Goto(0,1);
				u8 lcdsend2[19] = "3.Enter 4.logout";
				LCD_sendStr(lcdsend2[0]);
				ControlCounter = 1;
			}
			if (ControlCounter==1)
			{
				LCD_clearDis();
				//Keypad read
				recieve = KPD_read();
				if(recieve==INPUT_Light){
					//lighting
					LCD_sendStr("1.Hall 2.Entrance");
					recieve = KPD_read();
					if (recieve ==LIGHTINGROOM)
					{
						LIGHTING_Start(LIGHTINGROOM);
					}
					else if (recieve == LIGHTINHALL)
					{
						LIGHTING_Start(LIGHTINHALL);
					}
				}
				else if(recieve ==INPUT_Temp){
					//Temperature check
					TEMP_Check(OUTPUTLCD);
				}
				else if (recieve ==INPUT_ENTERANCE)
				{
					UART_sendStr("y and n");
					recieve = UART_receiveDataWait();
					if (recieve=='y')
					{
						DOORCONTROL_Start();
					}
				}
				else if (recieve == INPUT_LOGOUTUSER)
				{
					xEventGroupClearBits(UserEventGroup, BIT_0 );
				}
				ControlCounter = 0;
			}
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}
