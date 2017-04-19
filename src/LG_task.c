/*
 * LG_task.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

void LG_systemInit(void)
{

	cmu_Setup();
	letimer_Setup();
	LED_Init();
    /* Limit the lowest energy mode that the device can enter */
    blockSleepMode(LOWEST_ENERGY_MODE_ALLOWED);

    /* Start the LETIMER0 */
    LETIMER_Enable(LETIMER0, true);
}

void LETIMER0_IRQHandler(void)
{
    uint32_t int_Flag;
    CORE_CriticalDisableIrq();
    int_Flag = LETIMER_IntGet(LETIMER0);
    LETIMER_IntClear(LETIMER0, int_Flag);

    /* Determine pending interrupt */
    if ((int_Flag & _LETIMER_IF_COMP0_MASK) == _LETIMER_IF_COMP0_MASK)
    {

    }
    else if ((int_Flag & _LETIMER_IF_COMP1_MASK) == _LETIMER_IF_COMP1_MASK)
    {

    }

    CORE_CriticalEnableIrq();
}
