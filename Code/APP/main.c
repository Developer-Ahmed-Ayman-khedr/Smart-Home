/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "Code_APP.h"

int main(){

	//LoginEventGroup = xEventGroupCreate();

	//UserEventGroup = xEventGroupCreate();

	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&Code_APPInitDriversTaskHandle);

	xTaskCreate(LoginTask,NULL,100,NULL,3,&LoginTaskHandle);

	//xTaskCreate(OptionsTask,NULL,100,NULL,2,&OptionsTaskHandle);

	//xTaskCreate(AdminOptionsTask,NULL,100,NULL,2,&AdminOptionsTaskHandle);

	//xTaskCreate(UserOptionsTask,NULL,100,NULL,2,&UserOptionsTaskHandle);

	vTaskSuspend(LoginTaskHandle);

	//vTaskSuspend(OptionsTaskHandle);

	//vTaskSuspend(AdminOptionsTaskHandle);

	//vTaskSuspend(UserOptionsTaskHandle);

	vTaskStartScheduler();

	while (1){
	}
	return 0;
}
