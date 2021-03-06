/*
 * LG_systemConfig.h
 *
 *  Created on: Apr 18, 2017
 *      Author: shuting
 */

#ifndef INC_LG_SYSTEMCONFIG_H_
#define INC_LG_SYSTEMCONFIG_H_

#include "LG_system.h"

/*******************************************************************************
 ************************** SYSTEM CONFIGURATION *******************************
 ******************************************************************************/

#define LOWEST_ENERGY_MODE_ALLOWED		(EM2)

/* LETIMER USER CONFIGURATION */
#define OPERATING_PERIOD		(1.0)
#define OPERATING_SUBDURATION	(0.01)

/* AMBIENT LIGHT SENSOR DETECTION CONFIGURATION */
#define DARKNESS_THRESHOLD	(55)
#define LIGHTNESS_THRESHOLD	(60)

/* LEUART CONFIGURATION */
#define LEUART0_BAUDRATE					(9600)
#define LEUART0_DATABITS					(leuartDatabits8)
#define LEUART0_PARITY						(leuartNoParity)
#define LEUART0_STOPBIT						(leuartStopbits1)
#define LEUART0_ENABLE						(leuartEnable)
#define LEUART0_ROUTE_LOC					(LEUART_ROUTE_LOCATION_LOC0)

/* PIR sensor configuration */
#define PIR_TIMEOUT					(5000)
#endif /* INC_LG_SYSTEMCONFIG_H_ */
