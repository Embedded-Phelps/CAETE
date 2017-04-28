/*
 * LG_acmp.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */
#include "LG_system.h"

void acmp_Setup(void)
{
  /* ACMP configuration constant table. */
  static const ACMP_Init_TypeDef initACMP0 =
  {
    .fullBias = false,                 /* fullBias */
    .halfBias = true,                  /* halfBias */
    .biasProg =  0x0,                  /* biasProg */
    .interruptOnFallingEdge =  false,  /* interrupt on rising edge */
    .interruptOnRisingEdge =  false,   /* interrupt on falling edge */
    .warmTime = acmpWarmTime512,       /* 512 cycle warmup to be safe */
    .hysteresisLevel = acmpHysteresisLevel5, /* hysteresis level 5 */
    .inactiveValue = false,            /* inactive value */
    .lowPowerReferenceEnabled = false, /* low power reference */
    .vddLevel = 0x00,                  /* VDD level */
    .enable = false                    /* Don't request enabling. */
  };

  /* Configure the drive strength of the ports for the light sensor. */
  GPIO_DriveModeSet(AMBIANT_LIGHT_EXCITE_PORT, gpioDriveModeStandard);
  GPIO_DriveModeSet(AMBIANT_LIGHT_SENSE_PORT, gpioDriveModeStandard);

  /* Initialize the 2 GPIO pins of the light sensor setup. */
  GPIO_PinModeSet(AMBIANT_LIGHT_EXCITE_PORT, AMBIANT_LIGHT_EXCITE_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(AMBIANT_LIGHT_SENSE_PORT, AMBIANT_LIGHT_SENSE_PIN, gpioModeDisabled, 0);

  /* Configure ACMP. */
  ACMP_Init(ACMP0, &initACMP0);
  /* Disable ACMP0 out to a pin. */
  ACMP_GPIOSetup(ACMP0, 0, false, false);
  /* Set up ACMP negSel to VDD, posSel is controlled by LESENSE. */
  ACMP_ChannelSet(ACMP0, acmpChannelVDD, acmpChannel0);
  /* LESENSE controls ACMP thus ACMP_Enable(ACMP0) should NOT be called in order
   * to ensure lower current consumption. */

  /* ACMP capsense configuration constant table. */
  static const ACMP_CapsenseInit_TypeDef initACMP1 =
  {
      .fullBias                 = false,
      .halfBias                 = false,
      .biasProg                 =                  0x7,
      .warmTime                 = acmpWarmTime512,
      .hysteresisLevel          = acmpHysteresisLevel7,
      .resistor                 = acmpResistor0,
      .lowPowerReferenceEnabled = false,
      .vddLevel                 =                 0x3D,
      .enable                   = false
  };


  /* Configure ACMP locations, ACMP output to pin disabled. */
  ACMP_GPIOSetup(ACMP1, 0, false, false);

  /* Initialize ACMPs in capacitive sense mode. */
  ACMP_CapsenseInit(ACMP1, &initACMP1);

  /* Don't enable ACMP, LESENSE controls it! */
}
