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
		ADC_init();
		KPD_init();
		LCD_init();
		UART_init();

		HOLD_init();
		password_init();
		DOORCONTROL_init();
		EEPROMInitialize();

		vTaskResume(LoginTaskHandle);

		//vTaskSuspend(NULL);

		vTaskDelete(NULL);

		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void LoginTask(void * pvParameters ){
	while(1)
	{
		//vTaskSuspend(OptionsTaskHandle);

		if(CheckPasswordAdmin()==TRUE)
		{
			//xEventGroupSetBits(LoginEventGroup, ADMIN_BIT_0);

			//vTaskResume(OptionsTaskHandle);

			//vTaskResume(AdminOptionsTaskHandle);

			xTaskCreate(AdminOptionsTask,NULL,100,NULL,2,&AdminOptionsTaskHandle);

			vTaskSuspend(NULL);
		}
		if(UserLogin() == TRUE){
			//LCD_sendData('H');
			//xEventGroupSetBits(LoginTaskHandle,USER_BIT_1);

			//vTaskResume(OptionsTaskHandle);

			//vTaskResume(UserOptionsTaskHandle);

			xTaskCreate(UserOptionsTask,NULL,100,NULL,2,&UserOptionsTaskHandle);

			vTaskSuspend(NULL);
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void AdminOptionsTask(void * pvParameters ){
	u8 AdminControlCounter = 0;
	u8 Adminrecieve = UART_NOT_RECEIVE;
	while(1){
		//Admin Section

		if (AdminControlCounter==0)
		{
			//Correct password Welcome
			UART_sendStr("1.Light 2.Temp 3.Enter 4.Add User 5.Delete User 6.logout\r\n");
			AdminControlCounter = 1;
		}
		if (AdminControlCounter==1)
		{
			//UART read
			Adminrecieve = UART_receiveDataWait();

			if(Adminrecieve==INPUT_Light){
				//lighting
				UART_sendStr("1.Hall 2.Entrance\r\n");

				Adminrecieve = UART_receiveDataWait();

				if (Adminrecieve ==LIGHTINGROOM)
				{
					LIGHTING_Start(LIGHTINGROOM);
				}
				else if (Adminrecieve == LIGHTINHALL)
				{
					LIGHTING_Start(LIGHTINHALL);
				}
			}
			else if(Adminrecieve ==INPUT_Temp){
				//Temperature check
				TEMP_Check(OUTPUTUART);

			}

			else if (Adminrecieve ==INPUT_ENTERANCE)
			{
				UART_sendStr("\r\n");
				DOORCONTROL_Start();
				//ControlCounter = 0;
			}

			else if (Adminrecieve ==INPUT_ADDUSER)
			{
				//UART_sendStr("\r\n Add user data \r\n");
				//UART_sendStr("Enter user id\r\n");
				AddUser();
				//ControlCounter = 0;
			}
			else if (Adminrecieve == INPUT_DELETEUSER)
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
				Adminrecieve = UART_receiveDataWait()-48;
				DeleteUser(Adminrecieve);
				//ControlCounter = 0;
			}
			else if (Adminrecieve == INPUT_LOGOUTADMIN)
			{
				//xEventGroupClearBits(LoginEventGroup, ADMIN_BIT_0);
				vTaskResume(LoginTaskHandle);
				//vTaskSuspend(NULL);
				vTaskDelete(NULL);
			}
			AdminControlCounter = 0;
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void UserOptionsTask(void * pvParameters ){
	u8 UserControlCounter = 0;
	u8 UserRecieve = KPD_UNPRESSED;
	u8 lcdsend[20] = "1.Li2.T3.E4.log";
	while(1){
		switch (UserControlCounter)
		{
			case 0:
				//Correct password Welcome
				LCD_clearDis();
				//LCD_sendStr("1.Li 2.Tem 3.Ent 4.log");
				LCD_sendStr(lcdsend);
				//LCD_Goto(0,1);
				//UserControlCounter = 1;
				//LCD_sendData('H');
				//LCD_Goto(0,0);

				//LCD_sendStr("1.Light 2.Temp ");
				LCD_Goto(0,1);
				//LCD_sendStr("3.Enter4.logout");
				UserControlCounter = 1;
				break;
			case 1:
				//Keypad read
				UserRecieve = KPD_read();

				if (UserRecieve!=KPD_UNPRESSED)
				{
					while(KPD_read()!=KPD_UNPRESSED);

					LCD_sendData(UserRecieve);

					//lighting
					if(UserRecieve==INPUT_Light){
						//lighting
						LCD_clearDis();
						//LCD_sendStr("1.Hall 2.Entrance");
						LCD_sendData('H');
						LCD_sendData(' ');
						LCD_sendData('E');
						LCD_Goto(0,1);
						UserControlCounter = 2;
					}
					//else
					if(UserRecieve ==INPUT_Temp){
						//Temperature check
						LCD_clearDis();
						TEMP_Check(OUTPUTLCD);
						//_delay_ms(50);
						UserControlCounter = 0;
					}
					//else
					if (UserRecieve ==INPUT_ENTERANCE)
					{
						//UART_sendStr("y and n");
						UART_sendData('y');
						UART_sendData('n');
						UserRecieve = UART_receiveDataWait();
						if (UserRecieve=='y')
						{
							DOORCONTROL_Start();
						}
						UserControlCounter = 0;
					}
					//Logout for the user
					else if (UserRecieve == INPUT_LOGOUTUSER)
					{
						LCD_clearDis();
						//xEventGroupClearBits(LoginEventGroup, USER_BIT_1 );
						vTaskResume(LoginTaskHandle);
						//vTaskSuspend(NULL);
						vTaskDelete(NULL);
					}
				}
				break;
			case 2:
				//lighting
				//Keypad read
				UserRecieve = KPD_read();

				if (UserRecieve!=KPD_UNPRESSED)
				{
					while(KPD_read()!=KPD_UNPRESSED);

					LCD_sendData(UserRecieve);

					//lighting
					if (UserRecieve ==LIGHTINGROOM)
					{
						LIGHTING_Start(LIGHTINGROOM);
						UserControlCounter = 0;
					}
					else if (UserRecieve == LIGHTINHALL)
					{
						LIGHTING_Start(LIGHTINHALL);
						UserControlCounter = 0;
					}
				}
				break;
			default:
			break;
		}
	vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

/*void OptionsTask(void *pvParameters){
	static u8 ControlCounter = 0;
	EventBits_t uxBits;
	u8 recieve = UART_NOT_RECEIVE;
	while(1){
		vTaskSuspend(LoginTaskHandle);

		//Admin Section

		uxBits = xEventGroupWaitBits(LoginEventGroup, ADMIN_BIT_0 | USER_BIT_1, pdFALSE, pdFALSE, 0 );

		if(( uxBits & ADMIN_BIT_0 ) != 0){
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
					UART_sendStr("\r\n");
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
					xEventGroupClearBits(LoginEventGroup, ADMIN_BIT_0);
					vTaskResume(LoginTaskHandle);
					vTaskSuspend(NULL);
				}
				ControlCounter = 0;
			}
		}

		//User Section

		//uxBits = xEventGroupWaitBits(UserEventGroup, BIT_0, pdFALSE, pdFALSE, 0 );
		/*
		if(( uxBits & USER_BIT_1 ) != 0){


			switch (ControlCounter)
			{
			case 0:
				//Correct password Welcome

				LCD_Goto(0,0);
				LCD_clearDis();
				LCD_sendStr("1.Light 2.Temp ");
				LCD_Goto(0,1);
				LCD_sendStr("3.Enter4.logout");
				ControlCounter = 1;
				break;
			case 1:
				//Keypad read
				recieve = KPD_read();

				if (recieve!=KPD_UNPRESSED)
				{
					while(KPD_read()!=KPD_UNPRESSED);

					LCD_sendData(recieve);

					//lighting
					if(recieve==INPUT_Light){
						//lighting
						LCD_clearDis();
						LCD_sendStr("1.Hall 2.Entrance");
						LCD_Goto(0,1);
						ControlCounter = 2;
					}
					else if(recieve ==INPUT_Temp){
						//Temperature check
						LCD_clearDis();
						TEMP_Check(OUTPUTLCD);
						//_delay_ms(50);
						ControlCounter = 0;
					}
					else if (recieve ==INPUT_ENTERANCE)
					{
						UART_sendStr("y and n");
						recieve = UART_receiveDataWait();
						if (recieve=='y')
						{
							DOORCONTROL_Start();
						}
						ControlCounter = 0;
					}
					//Logout for the user
					else if (recieve == INPUT_LOGOUTUSER)
					{
						LCD_clearDis();
						xEventGroupClearBits(LoginEventGroup, USER_BIT_1 );
						vTaskResume(LoginTaskHandle);
						vTaskSuspend(NULL);
						ControlCounter = 0;
					}
				}

				break;
			case 2:
				//lighting
				//Keypad read
				recieve = KPD_read();

				if (recieve!=KPD_UNPRESSED)
				{
					while(KPD_read()!=KPD_UNPRESSED);

					LCD_sendData(recieve);

					//lighting
					if (recieve ==LIGHTINGROOM)
					{
						LIGHTING_Start(LIGHTINGROOM);
						ControlCounter = 0;
					}
					else if (recieve == LIGHTINHALL)
					{
						LIGHTING_Start(LIGHTINHALL);
						ControlCounter = 0;
					}
				}
				break;
			default:
				break;
			}
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}
*/
