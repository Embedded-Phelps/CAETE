/*
 * LG_cmu.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

void cmu_Setup(void)
{
#if LOWEST_ENERGY_MODE_ALLOWED == EM2
    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
#else
    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
#endif
    CMU_ClockEnable(cmuClock_CORELE, true);
    CMU_ClockEnable(cmuClock_LETIMER0, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_I2C1, true);

}
