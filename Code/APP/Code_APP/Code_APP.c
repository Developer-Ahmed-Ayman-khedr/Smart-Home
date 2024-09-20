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
		//Initialize the system Drivers
		GI_enable();
		ADC_init();
		KPD_init();
		LCD_init();
		UART_init();

		//Initialize the program features
		HOLD_init();
		password_init();
		DOORCONTROL_init();
		EEPROMInitialize();

		vTaskResume(LoginTaskHandle);
		vTaskDelete(NULL);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void LoginTask(void * pvParameters ){
	while(1)
	{
		if(CheckPasswordAdmin()==TRUE)
		{
			xTaskCreate(AdminOptionsTask,NULL,100,NULL,2,&AdminOptionsTaskHandle);
			vTaskSuspend(NULL);
		}
		if(UserLogin() == TRUE){
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
			//Correct password show options
			UART_sendStr("1.Light 2.Temp 3.Enter 4.Add User 5.Delete User 6.logout\r\n");
			AdminControlCounter = 1;
		}
		if (AdminControlCounter==1)
		{
			//UART read
			Adminrecieve = UART_receiveDataWait();

			if(Adminrecieve==INPUT_Light){
				//lighting
				UART_sendStr("1.Entrance 2.Hall\r\n");

				Adminrecieve = UART_receiveDataWait();

				if (Adminrecieve ==LIGHTINGENTRANCE)
				{
					LIGHTING_Start(LIGHTINGENTRANCE);
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
			}

			else if (Adminrecieve ==INPUT_ADDUSER)
			{
				AddUser();
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
				vTaskResume(LoginTaskHandle);
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

	u8 lcdsend[20] = "1.Li2.T3.E4.log"; //1.Light 2.Temp 3.Enter 4.logout
	while(1){
		switch (UserControlCounter)
		{
			case 0:
				//Correct password Show the options
				LCD_clearDis();
				LCD_sendStr(lcdsend);
				LCD_Goto(0,1);
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
						//1.Entrance 2.Hall
						LCD_sendData('E');
						LCD_sendData(' ');
						LCD_sendData('H');
						LCD_Goto(0,1);
						UserControlCounter = 2;
					}
					//else
					if(UserRecieve ==INPUT_Temp){
						//Temperature check
						LCD_clearDis();
						TEMP_Check(OUTPUTLCD);
						UserControlCounter = 0;
					}
					//else
					if (UserRecieve ==INPUT_ENTERANCE)
					{
						//Yes to open the door and no to keep it closed
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
						vTaskResume(LoginTaskHandle);
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
					if (UserRecieve ==LIGHTINGENTRANCE)
					{
						LIGHTING_Start(LIGHTINGENTRANCE);
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
