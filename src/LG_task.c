/*
 * LG_task.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

RTCDRV_TimerID_t rtc_ID;
struct bme280_t bme280;
uint8_t data_upload_flag = DATA_UPLOAD_ENABLED;

void capSenseScanCompleteCB(void);
void capSenseChTriggerCB(uint32_t channel_flag);
void LG_processLightSensingEvt(void);
void LG_processSliderSensingEvt(void);

/**************************************************************************
 *	@brief 	System modules initialization function
 **************************************************************************/
void LG_systemInit(void)
{
	// Initialization of RTCDRV driver
	RTCDRV_Init();

	// Reserve a timer for the BME280 Module
	RTCDRV_AllocateTimer( &rtc_ID );

	// Set up the CMU module
	cmu_Setup();

	// Set up the LETIMER module
	letimer_Setup();

	// Set up the I2C module
	i2c_Setup();

	// Set up the ACMP module
	acmp_Setup();

	// Set up the LESENSE module and register callback function
	lesense_Setup();
	lesense_SetupCallbacks(&capSenseScanCompleteCB, &capSenseChTriggerCB);

	// Set up the LEUART module
	leuart_Setup();

	// Set up the PIR sensing module
	pir_Init();

	// Initialize on-board LEDs
	LED_Init();

    // Limit the lowest energy mode that the device can enter
    blockSleepMode(LOWEST_ENERGY_MODE_ALLOWED);

    // Start the LETIMER0
    LETIMER_Enable(LETIMER0, true);
}

/**************************************************************************
 *	@brief 	Ambient light change event processing function
 *****************************************************************************/
void LG_processLightSensingEvt(void)
{
	static bool env_state = LIGHTNESS;	// The system is in light at default

	if(env_state == DARKNESS)	// System was in the dark, and light detected
	{
		env_state = LIGHTNESS;

		// Change LESENSE settings to detect darkness
		LESENSE_ScanStop();
		while (LESENSE_STATUS_SCANACTIVE & LESENSE_StatusGet()) ;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT &= ~0x6FFF;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT |= DARKNESS_THRESHOLD | LESENSE_CH_INTERACT_SETIF_NEGEDGE;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].EVAL &= ~LESENSE_CH_EVAL_COMP;
		LESENSE_ScanStart();
	}
	else	// System was in the light, and darkness detected
	{
		env_state = DARKNESS;

		// Change LESENSE settings to detect light
		LESENSE_ScanStop();
		while (LESENSE_STATUS_SCANACTIVE & LESENSE_StatusGet()) ;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT &= ~0x6FFF;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].INTERACT |= LIGHTNESS_THRESHOLD | LESENSE_CH_INTERACT_SETIF_LEVEL;
		LESENSE->CH[AMBIENT_LIGHT_CHANNEL].EVAL |= LESENSE_CH_EVAL_COMP_GE;
		LESENSE_ScanStart();
	}

	if(data_upload_flag == DATA_UPLOAD_ENABLED)
	{
		serial_SendPacket(AMBIENT_LIGHT, &env_state); // Send out ambient light changed notification
	}
}

/**************************************************************************
 *	@brief 	Capacitive slider touched event processing function
 *****************************************************************************/
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
	serial_SendPacket(CAP_TOUCHED, &n); // Send out the touched state

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

/*****************************************************************************
 * @brief  LETIMER timeout ISR
 *****************************************************************************/
void LETIMER0_IRQHandler(void)
{
    uint32_t int_Flag;
    CORE_CriticalDisableIrq();
    int_Flag = LETIMER_IntGet(LETIMER0);
    LETIMER_IntClear(LETIMER0, int_Flag);

    /* Determine pending interrupt */
    if ((int_Flag & _LETIMER_IF_COMP0_MASK) == _LETIMER_IF_COMP0_MASK)
    {
    	BME280_PowerOn();		// Supply power to the BME280 module
    }
    else if ((int_Flag & _LETIMER_IF_COMP1_MASK) == _LETIMER_IF_COMP1_MASK)
    {
    	bme280_enable(&bme280);		// Now the supply power stablized, enable the BME280 module for data readouts and sending
    }

    CORE_CriticalEnableIrq();
}
