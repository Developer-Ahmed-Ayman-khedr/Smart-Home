/*
 * WDT_PROG.c
 *
 *  Created on: May 16, 2024
 *      Author: DELL
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "WDT_INT.h"

void WDT_start(u8 time)
{
	SET_BIT(WDTCR,WDE);

	if(time == WDT_TIME0)
	{
		CLEAR_BIT(WDTCR,WDP0);
		CLEAR_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP2);
	}
	else if(time == WDT_TIME7)
	{
		SET_BIT(WDTCR,WDP0);
		SET_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP2);
	}
}

void WDT_stop()
{
	//WDTCR = 0b00011000;
	WDTCR = (1<<WDTOE) | (1<<WDE);
	WDTCR = 0x00;
}
