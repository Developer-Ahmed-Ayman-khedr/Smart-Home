/*
 * WDT_PROG.c
 *
 * Created: 5/15/2024 7:24:28 PM
 *  Author: ahmed
 */ 

#include "WDT_INT.h"


//Start WDT
void WDT_Start(u8 time){
	//Start
	SET_BIT(WDTCR,WDE);
	
	//Select Time
	switch (time)
	{
	case 1:
		CLEAR_BIT(WDTCR,WDP0);
		CLEAR_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP2);
		break;
	case 2:
		SET_BIT(WDTCR,WDP0);
		CLEAR_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP2);
		break;
	case 3:
		CLEAR_BIT(WDTCR,WDP0);
		SET_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP2);
		break;
	case 4:
		SET_BIT(WDTCR,WDP0);
		SET_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP2);
		break;
	case 5:
		SET_BIT(WDTCR,WDP0);
		CLEAR_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP2);
		break;
	case 6:
		SET_BIT(WDTCR,WDP0);
		CLEAR_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP2);
		break;
	case 7:
		CLEAR_BIT(WDTCR,WDP0);
		SET_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP2);
		break;
	case 8:
		SET_BIT(WDTCR,WDP0);
		SET_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP2);
		break;
	
	default:
		break;
	}
}

//Stop WDT
void WDT_Stop(){
	WDTCR = WDTCR |((1<<WDE)|(1<<WDTOE));
	WDTCR = 0;
}