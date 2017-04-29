/*
 * LG_cmu.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

/**************************************************************************
 *	@brief 	CMU modules setup function
 **************************************************************************/
void cmu_Setup(void)
{
	/* Select LFA clock source */
#if LOWEST_ENERGY_MODE_ALLOWED == EM2
    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
#else
    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
#endif
    /* Select LFB clock source */
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
    CMU_ClockEnable(cmuClock_CORELE, true);
    /* Enable clock for LETIMER0 */
    CMU_ClockEnable(cmuClock_LETIMER0, true);
    /* Enable clock for GPIO */
    CMU_ClockEnable(cmuClock_GPIO, true);
    /* Enable clock for I2C1 */
    CMU_ClockEnable(cmuClock_I2C1, true);
    /* Enable clock for ACMP0. */
    CMU_ClockEnable(cmuClock_ACMP0, true);
    /* Enable clock for ACMP1. */
    CMU_ClockEnable(cmuClock_ACMP1, true);
    /* Enable clock for LESENSE. */
    CMU_ClockEnable(cmuClock_LESENSE, true);
    /* Set clock divider for LESENSE. */
    CMU_ClockDivSet(cmuClock_LESENSE, cmuClkDiv_1);
    /* Enable clock for DMA */
    CMU_ClockEnable(cmuClock_DMA, true);
    /* Enable clock for LEUART */
    CMU_ClockEnable(cmuClock_LEUART0, true);

}
