/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "Code_APP.h"

int main(){
	LoginEventGroup = xEventGroupCreate();

	xQueue = xQueueCreate( 10, sizeof( u8 ) );

	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&Code_APPInitDriversTaskHandle);

	xTaskCreate(LoginTask,NULL,100,NULL,3,&LoginTaskHandle);

	xTaskCreate(OptionsTask,NULL,100,NULL,2,&OptionsTaskHandle);

	xTaskCreate(DoorControlTask,NULL,100,NULL,1,&DoorControlTaskHandle);

	A = xSemaphoreCreateBinary();

	xSemaphoreGive( A );

	vTaskStartScheduler();


	while (1){
	}
	return 0;
}
