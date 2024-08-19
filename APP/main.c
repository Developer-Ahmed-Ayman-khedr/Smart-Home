/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "Code_APP.h"

int main(){
	LoginEventGroup = xEventGroupCreate();

	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&Code_APPInitDriversTaskHandle);

	xTaskCreate(LoginTask,NULL,100,NULL,3,&LoginTaskHandle);

	xTaskCreate(OptionsTask,NULL,100,NULL,2,&OptionsTaskHandle);

	vTaskStartScheduler();


	while (1){
	}
	return 0;
}
