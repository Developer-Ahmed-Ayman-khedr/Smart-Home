/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "Code_APP.h"

int main(){
	TaskHandle_t xHandle1;
	TaskHandle_t xHandle2;
	TaskHandle_t xHandle3;
	TaskHandle_t xHandle4;
	TaskHandle_t xHandle5;
	LoginEventGroup = xEventGroupCreate();
	xQueue = xQueueCreate( 10, sizeof( u8 ) );
	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&xHandle1);
	xTaskCreate(UARTInputTask,NULL,100,NULL,2,&xHandle2);
	xTaskCreate(LoginTask,NULL,100,NULL,1,&xHandle3);
	xTaskCreate(OptionsTask,NULL,100,NULL,1,&xHandle4);
	xTaskCreate(DoorControlTask,NULL,100,NULL,1,&xHandle5);
	vTaskStartScheduler();
	while (1){
	}
	return 0;
}
