/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "Code_APP.h"

int main(){

	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&Code_APPInitDriversTaskHandle);

	xTaskCreate(LoginTask,NULL,100,NULL,3,&LoginTaskHandle);

	vTaskSuspend(LoginTaskHandle);

	vTaskStartScheduler();

	while (1){
	}
	return 0;
}
