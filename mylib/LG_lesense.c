/*
 * LG_lesense.c
 * This driver refer to the example lesense project provided by SiLab Inc.
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"
/**************************************************************************//**
 * @brief This vector stores the latest read values from LESENSE
 * @param LESENSE_CHANNELS Vector of channels.
 *****************************************************************************/
static volatile uint32_t channelValues[LESENSE_CHANNELS] =
{
/*  Ch0,   Ch1,   Ch2,   Ch3,   Ch4,   Ch5,   Ch6,   Ch7    */
  0, 0, 0, 0, 0, 0, 0, 0,
/*  Ch8,   Ch9,   Ch10,  Ch11,  Ch12,  Ch13,  Ch14,  Ch15   */
  0, 0, 0, 0, 0, 0, 0, 0
};


/**************************************************************************//**
 * @brief  This stores the maximum values seen by a channel
 * @param LESENSE_CHANNELS Vector of channels.
 *****************************************************************************/
static volatile uint32_t channelMaxValues[LESENSE_CHANNELS] =
{
/*  Ch0,   Ch1,   Ch2,   Ch3,   Ch4,   Ch5,   Ch6,   Ch7    */
  1, 1, 1, 1, 1, 1, 1, 1,
/*  Ch8,   Ch9,   Ch11,  Ch11,  Ch12,  Ch13,  Ch14,  Ch15   */
  1, 1, 1, 1, 1, 1, 1, 1
};

static const bool channeInUseForCap[LESENSE_CHANNELS] = LESENSE_CAPSENSE_CH_IN_USE;

/** Callback function for LESENSE interrupts. */
static void (*lesenseScanCb)(void);
/** Callback function for LESENSE interrupts. */
static void (*lesenseChCb)(uint32_t flag);

/**************************************************************************
 *	@brief 	LESENSE modules setup function
 **************************************************************************/
void lesense_Setup(void)
{
	uint8_t i, j;
	static bool init = true;

	/* Array for storing the calibration values. */
	static uint16_t capsenseCalibrateVals[4];

	/* LESENSE channel configuration constant table in sense mode. */
	//static const LESENSE_ChAll_TypeDef initChsSense = LESENSE_SCAN_CONF_WITH_CAPSENSE_SENSE;
	/* LESENSE channel configuration constant table in sleep mode. */
	static const LESENSE_ChAll_TypeDef initChsSleep = LESENSE_SCAN_CONF_WITH_CAPSENSE_SLEEP;

	/* LESENSE alternate excitation channel configuration constant table. */
	static const LESENSE_ConfAltEx_TypeDef initAltEx = LESENSE_LIGHTSENSE_ALTEX_CONF;
	/* LESENSE central configuration constant table. */
	static const LESENSE_Init_TypeDef initLESENSE =
	{
		.coreCtrl =
		{
			.scanStart = lesenseScanStartPeriodic,
			.prsSel = lesensePRSCh0,
			.scanConfSel = lesenseScanConfDirMap,
			.invACMP0 = false,
			.invACMP1 = false,
			.dualSample = false,
			.storeScanRes = false,
			.bufOverWr = true,
			.bufTrigLevel = lesenseBufTrigHalf,
			.wakeupOnDMA = lesenseDMAWakeUpDisable,
			.biasMode = lesenseBiasModeDutyCycle,
			.debugRun = false
		},

		.timeCtrl =
		{
			.startDelay = 0U
		},

		.perCtrl =
		{
			.dacCh0Data = lesenseDACIfData,
			.dacCh0ConvMode = lesenseDACConvModeDisable,
			.dacCh0OutMode = lesenseDACOutModeDisable,
			.dacCh1Data = lesenseDACIfData,
			.dacCh1ConvMode = lesenseDACConvModeDisable,
			.dacCh1OutMode = lesenseDACOutModeDisable,
			.dacPresc = 0U,
			.dacRef = lesenseDACRefBandGap,
			.acmp0Mode = lesenseACMPModeMuxThres,
			.acmp1Mode = lesenseACMPModeMuxThres,
			.warmupMode = lesenseWarmupModeNormal
		},

		.decCtrl =
		{
			.decInput = lesenseDecInputSensorSt,
			.initState = 0U,
			.chkState = false,
			.intMap = true,
			.hystPRS0 = false,
			.hystPRS1 = false,
			.hystPRS2 = false,
			.hystIRQ = false,
			.prsCount = true,
			.prsChSel0 = lesensePRSCh0,
			.prsChSel1 = lesensePRSCh1,
			.prsChSel2 = lesensePRSCh2,
			.prsChSel3 = lesensePRSCh3
		}
	};

	/* Only initialize main LESENSE parameters once. */
	if (init)
	{
		/* Initialize LESENSE interface with RESET. */
		LESENSE_Init(&initLESENSE, true);
	}

	/* Stop LESENSE before configuration. */
	LESENSE_ScanStop();

	/* Wait until the currently active scan is finished. */
	while (LESENSE_STATUS_SCANACTIVE & LESENSE_StatusGet()) ;

	/* Clear result buffer. */
	LESENSE_ResultBufferClear();

	/* Set scan frequency (in Hz). */
	(void) LESENSE_ScanFreqSet(0U, 5U);

	/* Set clock divisor for LF clock. */
	LESENSE_ClkDivSet(lesenseClkLF, lesenseClkDiv_1);

	/* Configure scan channels. */
	LESENSE_ChannelAllConfig(&initChsSleep);

	/* Configure alternate excitation channels. */
	LESENSE_AltExConfig(&initAltEx);

	/* Restore calibration values. */
	LESENSE_ChannelThresSet(CAPLESENSE_SLIDER0_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[0]);
	LESENSE_ChannelThresSet(CAPLESENSE_SLIDER1_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[1]);
	LESENSE_ChannelThresSet(CAPLESENSE_SLIDER2_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[2]);
	LESENSE_ChannelThresSet(CAPLESENSE_SLIDER3_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[3]);

	/* Disable scan complete interrupt. */
	LESENSE_IntDisable(LESENSE_IEN_SCANCOMPLETE);

	NVIC_EnableIRQ(LESENSE_IRQn);

	/* Start scanning LESENSE channels. */
	LESENSE_ScanStart();

	/* Run it only once. */
	if (init)
	{
		/* Assuming that the pads are not touched at first, we can use the result as
		 * the threshold value to calibrate the capacitive sensing in LESENSE. */
		init = false;

		/* Waiting for buffer to be full. */
		while (!(LESENSE->STATUS & LESENSE_STATUS_BUFHALFFULL)) ;

		/* Read out steady state values from LESENSE for calibration. */
		for (i = 0U, j = 0U; j < LESENSE_CHANNELS; j++)
		{
			if (channeInUseForCap[j])
			{
				if (i < CAPLESENSE_NUMOF_SLIDERS)
				{
					capsenseCalibrateVals[i] = LESENSE_ScanResultDataBufferGet(j) - CAPLESENSE_SENSITIVITY_OFFS;
				}
				i++;
			}
		}

		/* Set calibration values. */
		LESENSE_ChannelThresSet(CAPLESENSE_SLIDER0_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[0]);
		LESENSE_ChannelThresSet(CAPLESENSE_SLIDER1_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[1]);
		LESENSE_ChannelThresSet(CAPLESENSE_SLIDER2_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[2]);
		LESENSE_ChannelThresSet(CAPLESENSE_SLIDER3_PIN, CAPLESENSE_ACMP_VDD_SCALE, capsenseCalibrateVals[3]);
	}
}

/**************************************************************************//**
 * @brief  LESENSE callback setup
 * @param  scanCb Scan callback
 * @param  chCb Channel callback
 *****************************************************************************/
void lesense_SetupCallbacks(void (*scanCb)(void), void (*chCb)(uint32_t flag))
{
  lesenseScanCb = scanCb;
  lesenseChCb   = chCb;
}

/**************************************************************************//**
 * @brief  LESENSE interrupt handler
 *****************************************************************************/
void LESENSE_IRQHandler(void)
{
  uint32_t count;
  uint32_t lesense_int_flag;
  uint8_t capChannel;

  lesense_int_flag = LESENSE_IntGetEnabled();
  LESENSE_IntClear(lesense_int_flag);

  /* LESENSE scan complete interrupt. */
  if (LESENSE_IF_SCANCOMPLETE & lesense_int_flag)
  {
    /* Iterate trough all channels */
    for (capChannel = 8; capChannel <= SLIDER_PART3_CHANNEL; capChannel++)
    {
      /* Read out value from LESENSE buffer */
      count = LESENSE_ScanResultDataGet();

      /* Store value in channelValues */
      channelValues[capChannel] = count;

      /* Update channelMaxValues */
      if (count > channelMaxValues[capChannel])
      {
        channelMaxValues[capChannel] = count;
      }
    }

    /* Call callback function. */
    if (lesenseScanCb != 0x00000000)
    {
      lesenseScanCb();
    }
  }

  /* LESENSE channel interrupt. */
  if (LESENSE_CHANNEL_INT & lesense_int_flag)
  {

    /* Call callback function. */
    if (lesenseChCb != 0x00000000)
    {
      lesenseChCb(lesense_int_flag);
    }
  }
}

/**************************************************************************//**
 * @brief Get the position of the slider
 * @return The position of the slider if it can be determined,
 *         -1 otherwise.
 *****************************************************************************/
int32_t lesense_GetSliderPosition(void)
{
	int i;
	int minPos = -1;
	uint32_t minVal = 236; /* adjust it */

	/* Values used for interpolation. There is two more which represents the edges.
	 * This makes the interpolation code a bit cleaner as we do not have to make special
	 * cases for handling them */
	uint32_t interpol[6]      = { 255, 255, 255, 255, 255, 255 };
	uint32_t channelPattern[] = { 0, SLIDER_PART0_CHANNEL + 1, SLIDER_PART1_CHANNEL + 1, SLIDER_PART2_CHANNEL + 1, SLIDER_PART3_CHANNEL + 1 };

	/* The calculated slider position. */
	int position;

	/* Iterate through the 4 slider bars and calculate the current value divided by
	 * the maximum value multiplied by 256.
	 * Note that there is an offset of 1 between channelValues and interpol.
	 * This is done to make interpolation easier.
	 */
	for (i = 1; i < CAPLESENSE_NUMOF_SLIDERS + 1; i++)
	{
		/* interpol[i] will be in the range 0-256 depending on channelMax */
		interpol[i]  = channelValues[channelPattern[i] - 1] << 8;
		interpol[i] /= channelMaxValues[channelPattern[i] - 1];
		/* Find the minimum value and position */
		if (interpol[i] < minVal)
		{
			minVal = interpol[i];
			minPos = i;
		}
	}
	/* Check if the slider has not been touched */
	if (minPos == -1)
		return -1;

	/* Start position. Shift by 4 to get additional resolution. */
	/* Because of the interpol trick earlier we have to substract one to offset that effect */
	position = (minPos - 1) << 4;

	/* Interpolate with pad to the left */
	position -= ((256 - interpol[minPos - 1]) << 3) / (256 - interpol[minPos]);

	/* Interpolate with pad to the right */
	position += ((256 - interpol[minPos + 1]) << 3) / (256 - interpol[minPos]);

	return position;
}
