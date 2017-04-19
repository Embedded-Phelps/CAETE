//=========================================================
// File: include.h:
// This file includes all the header files that are used by
// this program.
//
// Author: ShuTing Guo
// Date: 01/31/2017
//=========================================================
#ifndef INC_LG_SYSTEM_H__
#define INC_LG_SYSTEM_H__

/*******************************************************************************
 *****************************  STANDARD LIB  **********************************
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/*******************************************************************************
 ***************************** SILAB EMLIB  ***********************************
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "em_letimer.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_acmp.h"
#include "em_adc.h"
#include "em_dma.h"
#include "em_i2c.h"
#include "em_leuart.h"
#include "em_lesense.h"

/*******************************************************************************
 ***************************** SILAB DRIVER  ***********************************
 ******************************************************************************/

#include "dmactrl.h"

/*******************************************************************************
 ********************************  MYLIB  ***********************************
 ******************************************************************************/
#include "LG_systemConfig.h"
#include "LG_task.h"
#include "LG_cmu.h"
#include "LG_letimer.h"

#include "board_led.h"
#include "sleep.h"

/*******************************************************************************
 *****************************  SYSTEM MACRO  **********************************
 ******************************************************************************/

/* System Energy Modes */
#define EM0		(0U)
#define EM1		(1U)
#define EM2		(2U)
#define EM3		(3U)

#define I2C_EM	(EM1)	// Lowest energy mode allowed when I2C is in operation

/* System Clocks */
#define ULFRCO_DEFAULT_FREQ					(1000)			// The default frequency of the ULFRCO clock
#define LFXO_DEFAULT_FREQ					(32768)			// The default frequency of the LFXO clock
#define LETIMER2_LFXO_DEFAULT_MAX_PERIOD	(2)				// The default max timing period of LETIMER0 clocked by LFXO in seconds
#define CMU_LFAPRESC0_LETIMER0_MAX_DIV		(32768)			// Max value of the LETIMER0 low frequency prescaler divisor

/*******************************************************************************
 *****************************  BOARD SPECIFIC  ********************************
 ******************************************************************************/

/* On-Board Ambient Light Sensor */
#define AMBIANT_LIGHT_EXCITE_PORT				(gpioPortD)
#define AMBIANT_LIGHT_EXCITE_PIN				(6U)
#define AMBIANT_LIGHT_SENSE_PORT				(gpioPortC)
#define AMBIANT_LIGHT_SENSE_PIN					(6U)

/* LEUART TX/RX pin location based on the user define */
#if (LEUART0_ROUTE_LOC == LEUART_ROUTE_LOCATION_LOC0)
	#define	LEUART0_TX_PORT						(gpioPortD)
	#define LEUART0_TX_PIN						(4)
	#define LEUART0_RX_PORT						(gpioPortD)
	#define LEUART0_RX_PIN						(5)
#else
#if (LEUART0_ROUTE_LOC == LEUART_ROUTE_LOCATION_LOC1)
	#define	LEUART0_TX_PORT						(gpioPortB)
	#define LEUART0_TX_PIN						(13)
	#define LEUART0_RX_PORT						(gpioPortB)
	#define LEUART0_RX_PIN						(14)
#else
#if (LEUART0_ROUTE_LOC == LEUART_ROUTE_LOCATION_LOC2)
	#define	LEUART0_TX_PORT						(gpioPortE)
	#define LEUART0_TX_PIN						(14)
	#define LEUART0_RX_PORT						(gpioPortE)
	#define LEUART0_RX_PIN						(15)
#else
#if (LEUART0_ROUTE_LOC == LEUART_ROUTE_LOCATION_LOC3)
	#define	LEUART0_TX_PORT						(gpioPortF)
	#define LEUART0_TX_PIN						(0)
	#define LEUART0_RX_PORT						(gpioPortF)
	#define LEUART0_RX_PIN						(1)
#else
#if (LEUART0_ROUTE_LOC == LEUART_ROUTE_LOCATION_LOC4)
	#define	LEUART0_TX_PORT						(gpioPortA)
	#define LEUART0_TX_PIN						(0)
	#define LEUART0_RX_PORT						(gpioPortF)
	#define LEUART0_RX_PIN						(2)
#endif
#endif
#endif
#endif
#endif


/* On-Board LED0/1 */
#define BOARD_LED0_PORT						(gpioPortE)
#define BOARD_LED0_PIN						(2U)
#define BOARD_LED1_PORT						(gpioPortE)
#define BOARD_LED1_PIN						(3U)

#define BOARD_NO_OF_LEDS					(2)
#define BOARD_GPIO_LEDARRAY_INIT 			{{BOARD_LED0_PORT,BOARD_LED0_PIN},{BOARD_LED1_PORT,BOARD_LED1_PIN}}

/* I2C */
#define I2C1_SDA_PORT						(gpioPortC)
#define I2C1_SDA_PIN						(4U)
#define I2C1_SCL_PORT						(gpioPortC)
#define I2C1_SCL_PIN						(5U)
#define I2C_WRITE							(0U)
#define I2C_READ							(1U)

/*******************************************************************************
 ************************  EXTERNAL GLOBAL VARIABLE  ***************************
 ******************************************************************************/

#endif /* LG_SYSTEM_H_ */

