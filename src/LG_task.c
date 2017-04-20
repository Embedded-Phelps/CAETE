/*
 * LG_task.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

RTCDRV_TimerID_t rtc_ID;
struct bme280_t bme280;

void LG_systemInit(void)
{
	// Initialization of RTCDRV driver
	RTCDRV_Init();

	// Reserve a timer
	RTCDRV_AllocateTimer( &rtc_ID );

	cmu_Setup();
	letimer_Setup();
	i2c_Setup();
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
    	BME280_PowerOn();
    }
    else if ((int_Flag & _LETIMER_IF_COMP1_MASK) == _LETIMER_IF_COMP1_MASK)
    {
    	bme280_enable(&bme280);
    }

    CORE_CriticalEnableIrq();
}
