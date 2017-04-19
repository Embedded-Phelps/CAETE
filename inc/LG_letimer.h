/*
 * LG_letimer.h
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#ifndef INC_LG_LETIMER_H_
#define INC_LG_LETIMER_H_

#include "LG_system.h"

#if LOWEST_ENERGY_MODE_ALLOWED != EM2
#define COMP0  				( ULFRCO_DEFAULT_FREQ * OPERATING_PERIOD )		// The value for LETIMER0_COMP0 register
#define COMP1				( ULFRCO_DEFAULT_FREQ * (OPERATING_PERIOD - OPERATING_SUBDURATION))	// The value for LETIMER0_COMP1 register
#else
#define COMP0  				( LFXO_DEFAULT_FREQ * OPERATING_PERIOD )			// The value for LETIMER0_COMP0 register
#define COMP1				( LFXO_DEFAULT_FREQ * (OPERATING_PERIOD - OPERATING_SUBDURATION))	// The value for LETIMER0_COMP1 register
#endif

#define LETIMER0_LFXO_DEFAULT_MAX_PERIOD	(2)
#define LETIMER0_CMU_LFAPRESC0_MAX_DIV		(32768)

void letimer_Setup(void);

#endif /* INC_LG_LETIMER_H_ */
