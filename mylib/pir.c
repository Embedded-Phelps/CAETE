/*
 * pir.c
 *
 *  Created on: Apr 21, 2017
 *      Author: shuting
 */
#include "LG_system.h"

RTCDRV_TimerID_t rtc_PIR;
static bool old_state = NO_MOTION_DETECTED;

void pir_Init(void);
void GPIO_ODD_IRQHandler(void);
void pir_RTCCallback(RTCDRV_TimerID_t id);

void pir_Init(void)
{
	RTCDRV_AllocateTimer( &rtc_PIR );

    GPIO_PinModeSet(PIR_INT_PORT, PIR_INT_PIN, gpioModeInput, 0);
    GPIO_IntConfig(PIR_INT_PORT, PIR_INT_PIN, PIR_INT_RISINGEDGE, PIR_INT_FALLINGEDGE, PIR_INT_ENABLE);

    NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
    NVIC_EnableIRQ(GPIO_ODD_IRQn);
}

/* Ext GPIO interrupt routine */
void GPIO_ODD_IRQHandler(void)
{

	CORE_CriticalDisableIrq();
	if (old_state == NO_MOTION_DETECTED)
	{
		old_state = MOTION_DETECTED;
		//Send Notification
		serial_Sendpacket(MOTION, 1);
	}
	RTCDRV_StartTimer(rtc_PIR, rtcdrvTimerTypeOneshot, PIR_TIMEOUT, pir_RTCCallback, NULL);
	GPIO_IntClear(1 << PIR_INT_NO);
	CORE_CriticalEnableIrq();
}

void pir_RTCCallback(RTCDRV_TimerID_t id)
{
	old_state = NO_MOTION_DETECTED;
}
