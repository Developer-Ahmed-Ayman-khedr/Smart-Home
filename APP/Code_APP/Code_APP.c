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

		LIGHTING_init();
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

			vTaskResume(OptionsTaskHandle);

			vTaskSuspend(LoginTaskHandle);
		}
		else if(UserLogin() == TRUE){
			xEventGroupClearBits( LoginEventGroup, BIT_0 );
			vTaskResume(OptionsTaskHandle);

			vTaskSuspend(LoginTaskHandle);
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void OptionsTask(void *pvParameters){
	//u8 var2 = 'a';
	//u8 read = 0;
	static u8 ControlCounter = 0;
	static u8 UARTInput = UART_NOT_RECEIVE;
	while(1){
		uxBits = xEventGroupWaitBits(LoginEventGroup, BIT_0, pdTRUE, pdFALSE, 0 );
		if(( uxBits & BIT_0 ) != 0){
			if (ControlCounter==0)
			{
				//Correct password Welcome
				UART_sendStr("1.Light 2.Temp 3.Enter 4.Add User 5.Delete User\r\n");
				ControlCounter = 1;
			}
			//UART read
			u8 recieve = UART_receiveDataWait() ;
			if(recieve==INPUT_Light){
				//lighting
				UART_sendStr("1.Hall 2.Entrance\r\n");
				recieve = UART_receiveDataWait() ;
				if (recieve ==LIGHTINGROOM)
				{
					LIGHTING_Start(LIGHTINGROOM);
				}
				else if (recieve == LIGHTINHALL)
				{
					LIGHTING_Start(LIGHTINHALL);
				}
				ControlCounter = 0;
			}
			else if(recieve ==INPUT_Temp){
				//Temperature check
				TEMP_Check();
				UART_sendStr("\r\n1 to return:  \r\n");
				if(recieve ==INPUT_RETURN){
					ControlCounter = 0;
				}
			}

			else if (recieve ==INPUT_ENTERANCE)
			{
				DOORCONTROL_Start();
				ControlCounter = 0;
			}

			else if (recieve ==INPUT_ADDUSER)
			{
				//UART_sendStr("\r\n Add user data \r\n");
				UART_sendStr("\r\nEnter user id\r\n");
				AddUser();
				ControlCounter = 0;
			}
			else if (recieve == INPUT_DELETEUSER)
			{
				UART_sendStr("\r\nEnter user id\r\n");
				// show the saved users for admin to delete from them
				for (u8 i=4 ; i<24 ; i++)
				{
					UART_sendData(EEPROMValues[i]);
					if (i==8||i==13||i==18||i==23)
					{
						UART_sendData('*') ;
					}
				}
				recieve = UART_receiveDataWait() ;
				DeleteUser(recieve);
				ControlCounter = 0;
			}
		}
			/*else if(( uxBits & BIT_0 ) != 1){
				LCD_sendStr("1.Light 2.Temp 3.Enter");
				LCD_GoTo(0,1);
				if(INPUT_Read()==INPUT_Light){
					LCD_sendData('1');
				}
				else if(INPUT_Read()==INPUT_Temp){
					LCD_sendData('2');
				}
				else if(INPUT_Read()==INPUT_ENTERANCE){
					LCD_sendData('3');
				}

				LCD_clearDis();
				LCD_GoTo(0,0);
				LCD_sendStr("1.Hall 2.Entrance");
				LCD_GoTo(0,1);
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_LIGHTINGROOM);
					LIGHTING_Start(LIGHTINGROOM);
				}
				else if(INPUT_Read()=='2'){
					LCD_sendData(INPUT_LIGHTINHALL);
					LIGHTING_Start(LIGHTINHALL);
				}
				LCD_GoTo(0,0);
				TEMP_Check();
				LCD_GoTo(0,1);
				LCD_sendStr("1 to return:  ");
				read = INPUT_Read();
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_return);
				}
			}*/
			//xSemaphoreGive( A );
		//}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void DoorControlTask (void * pvParameters ){
	//u8 DoorKey ;
	while(1)
	{
		/*if (xQueueReceive(xQueue,&DoorKey,0)== pdPASS)
		{
			if(DoorKey==1)
			{
				DOORCONTROL_Start();
			}
		}*/
		vTaskDelay(250/portTICK_PERIOD_MS);
	}
}
