//===============================================================================
// File: board_led.h
// Generic on-board/external LEDs APIs header files
//
// Author: ShuTing Guo
// Date: 01/31/2017
//===============================================================================

#ifndef INC_BOARD_LED_H_
#define INC_BOARD_LED_H_

#define LED0	(0U)
#define LED1	(1U)

typedef struct
{
  GPIO_Port_TypeDef port;
  uint8_t        	pin;
} board_Led_Array;

/**********************************************************************/
/* Name: LED_Init()
 * Routine to set up the on-board LED
 *
 */
void LED_Init(void);

/**********************************************************************/
/* Name: board_LedOff()
 * Routine to turn off a LED
 *
 * Input variables: ledNo - the number of the LED to turn off
 * Global variables: led_Array[] - LED array
 * Returned variables: none defined
 *
 */
void LED_Off(uint8_t ledNo);

/**********************************************************************/
/* Name: board_LedOn()
 * Routine to turn on a LED
 *
 * Input variables: ledNo - the number of the LED to turn on
 * Global variables: led_Array[] - LED array
 * Returned variables: none defined
 *
 */
void LED_On(uint8_t ledNo);

#endif /* INC_BOARD_LED_H_ */
