//===============================================================================
// File: board_led.c
// Generic on-board/external LEDs APIs
//
// Author: ShuTing Guo
// Date: 01/31/2017
//===============================================================================

#include "LG_system.h"

/*******************************************************************************
 ****************************  Global Variables  *******************************
 ******************************************************************************/

static const board_Led_Array led_Array[ BOARD_NO_OF_LEDS ] = BOARD_GPIO_LEDARRAY_INIT;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/**********************************************************************/
/* Name: LED_Init()
 * Routine to set up the on-board LED
 *
 */
void LED_Init(void)
{
	GPIO_PinModeSet(BOARD_LED0_PORT, BOARD_LED0_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(BOARD_LED1_PORT, BOARD_LED1_PIN, gpioModePushPull, 0);
}

/**********************************************************************/
/* Name: LED_Off()
 * Routine to turn off a LED
 *
 * Input variables: ledNo - the number of the LED to turn off
 * Global variables: led_Array[] - LED array
 * Returned variables: none defined
 *
 */
void LED_Off(uint8_t ledNo)
{
  if ((ledNo >= 0) && (ledNo < BOARD_NO_OF_LEDS))
  {
    GPIO_PinOutClear(led_Array[ledNo].port, led_Array[ledNo].pin);
  }
}

/**********************************************************************/
/* Name: LED_On()
 * Routine to turn on a LED
 *
 * Input variables: ledNo - the number of the LED to turn on
 * Global variables: led_Array[] - LED array
 * Returned variables: none defined
 *
 */
void LED_On(uint8_t ledNo)
{
  if ((ledNo >= 0) && (ledNo < BOARD_NO_OF_LEDS))
  {
    GPIO_PinOutSet(led_Array[ledNo].port, led_Array[ledNo].pin);
  }
}
