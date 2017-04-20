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
#define DARKNESS_THRESHOLD	(0x38)
#define LIGHTNESS_THRESHOLD	(0x80)

#endif /* INC_LG_SYSTEMCONFIG_H_ */
