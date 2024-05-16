/*
 * GI_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: ahmed
 */

#include "GI_INT.h"

void GI_enable(){
	SET_BIT(SREG,I);
}

void GI_desable(){
	CLEAR_BIT(SREG,I);
}
