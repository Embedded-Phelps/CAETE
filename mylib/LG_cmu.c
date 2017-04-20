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
    /* Enable clock for ACMP0. */
    CMU_ClockEnable(cmuClock_ACMP0, true);
    /* Enable clock for ACMP1. */
    CMU_ClockEnable(cmuClock_ACMP1, true);
    /* Enable clock for LESENSE. */
    CMU_ClockEnable(cmuClock_LESENSE, true);
    /* Enable clock divider for LESENSE. */
    CMU_ClockDivSet(cmuClock_LESENSE, cmuClkDiv_1);

}
