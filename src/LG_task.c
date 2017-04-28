/*
 * LG_task.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

RTCDRV_TimerID_t rtc_ID;
struct bme280_t bme280;
uint8_t data_upload_flag = DATA_UPLOAD_DISABLED;

void capSenseScanCompleteCB(void);
void capSenseChTriggerCB(uint32_t channel_flag);
void LG_processLightSensingEvt(void);
void LG_processSliderSensingEvt(void);

void LG_systemInit(void)
{
	// Initialization of RTCDRV driver
	RTCDRV_Init();

	// Reserve a timer
	RTCDRV_AllocateTimer( &rtc_ID );

	cmu_Setup();
	letimer_Setup();
	i2c_Setup();
	acmp_Setup();

	lesense_Setup(true);
	lesense_SetupCallbacks(&capSenseScanCompleteCB, &capSenseChTriggerCB);
	leuart_Setup();
	//pir_Init();
	LED_Init();
    /* Limit the lowest energy mode that the device can enter */
    blockSleepMode(LOWEST_ENERGY_MODE_ALLOWED);

    /* Start the LETIMER0 */
    LETIMER_Enable(LETIMER0, true);
}

void LG_processLightSensingEvt(void)
{
	static bool env_state = LIGHTNESS;
	if(env_state == DARKNESS)
	{
		env_state = LIGHTNESS;
		//turn off led
		LESENSE_ScanStop();

	    /* Wait until the currently active scan is finished. */
		while (LESENSE_STATUS_SCANACTIVE & LESENSE_StatusGet()) ;

		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT &= ~0x6FFF;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT |= DARKNESS_THRESHOLD | LESENSE_CH_INTERACT_SETIF_NEGEDGE;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].EVAL &= ~LESENSE_CH_EVAL_COMP;
		LESENSE_ScanStart();
	}
	else
	{
		env_state = DARKNESS;
		LESENSE_ScanStop();

	    /* Wait until the currently active scan is finished. */
		while (LESENSE_STATUS_SCANACTIVE & LESENSE_StatusGet()) ;
		//turn on LED
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT &= ~0x6FFF;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT |= LIGHTNESS_THRESHOLD | LESENSE_CH_INTERACT_SETIF_LEVEL;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].EVAL |= LESENSE_CH_EVAL_COMP_GE;
		LESENSE_ScanStart();
	}
	if(data_upload_flag == DATA_UPLOAD_ENABLED)
	{
		serial_SendPacket(AMBIENT_LIGHT, &env_state); //???0->1
	}
}

void LG_processSliderSensingEvt(void)
{
	static uint8_t n = TURN_OFF;

	if (n == TURN_OFF)
	{
		LED_On(1);
		n=TURN_ON;
	}
	else
	{
		LED_Off(1);
		n=TURN_OFF;
	}
	serial_SendPacket(CAP_TOUCHED, &n);

}

/**************************************************************************//**
 * @brief  Callback for sensor scan complete.
 *****************************************************************************/
void capSenseScanCompleteCB(void)
{
	;
}

/**************************************************************************//**
 * @brief  Callback for sensor channel triggered.
 *****************************************************************************/
void capSenseChTriggerCB(uint32_t channel_flag)
{
	if(LESENSE_CHANNEL_INT_AMBIENT_LIGHT & channel_flag)
	{
		LG_processLightSensingEvt();
	}
	if(LESENSE_CHANNEL_INT_SLIDER & channel_flag)
	{
		LG_processSliderSensingEvt();
	}
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
