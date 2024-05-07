/*
 * GI_PROG.c
 *
 * Created: 4/24/2024 7:49:53 PM
 *  Author: ahmed
 */ 

#include "GI_INT.h"

void GI_enable(){
	SET_BIT(SREG,I);
}

void GI_desable(){
	CLEAR_BIT(SREG,I);
}