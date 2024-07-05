/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: ahmed, Abdo  and Hady
 */

#include "Code_APP.h"

int main(){
	TaskHandle_t xHandle1;
	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&xHandle1);

	vTaskStartScheduler();

	while (1){
		Code_APP();
	}
	return 0;
}
