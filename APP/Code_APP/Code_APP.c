/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include"Code_APP.h"

void Code_APPInitDriversTask(void *pvParameters){
	while(1){
		GI_enable();
		KPD_init();
		LCD_init();
		UART_init();

		//LIGHTING_init();
		//HOLD_init();
		//DOORCONTROL_init();
		vTaskSuspend(NULL);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void LoginTask(void * pvParameters ){
	while(1)
	{
		vTaskSuspend(OptionsTaskHandle);
		//if( xSemaphoreTake( A, 0 ) == pdTRUE ){
			if(CheckPasswordAdmin()==TRUE)
			{
				xEventGroupSetBits(LoginEventGroup, BIT_0);

				vTaskResume(OptionsTaskHandle);

				vTaskSuspend(LoginTaskHandle);

				//xSemaphoreGive( A );
			}
			else
			if(CheckDataForUser() == TRUE){
				xEventGroupClearBits( LoginEventGroup, BIT_0 );
				vTaskResume(OptionsTaskHandle);

				vTaskSuspend(LoginTaskHandle);
			}
		//}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void OptionsTask(void *pvParameters){
	//u8 var2 = 'a';
	//u8 read = 0;
	while(1){
		//if( xSemaphoreTake( A, 0 ) == pdTRUE )
		//{

			uxBits = xEventGroupWaitBits(LoginEventGroup, BIT_0, pdTRUE, pdFALSE, 0 );
			if(( uxBits & BIT_0 ) != 0){
				//Correct password Welcome
				UART_sendStr("1.Light 2.Temp 3.Enter 4.Add User\r\n");

				//UART read
				if(UART_receiveData()==INPUT_Light){
					//lighting
					UART_sendStr("1.Hall 2.Entrance\r\n");
					if (UART_receiveData()==LIGHTINGROOM)
					{
						LIGHTING_Start(LIGHTINGROOM);
					}
					else if (UART_receiveData()==LIGHTINHALL)
					{
						LIGHTING_Start(LIGHTINHALL);
					}
				}
				else if(UART_receiveData()==INPUT_Temp){
					//Temperature check
					TEMP_Check();
					UART_sendStr("\r\n1 to return:  \r\n");
				}
				else if (UART_receiveData()==INPUT_ENTERANCE)
				{
					DOORCONTROL_Start();
				}
				else if (UART_receiveData()== INPUT_ADDUSER)
				{
					//UART_sendStr("\r\n Add user data \r\n");
					AddUser();
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
		vTaskDelay(10/portTICK_PERIOD_MS);
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
