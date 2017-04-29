/*
 * LG_letimer.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

/*******************************************************************************
 ****************************  Global Variables  *******************************
 ******************************************************************************/

uint32_t letimer0_comp0 = COMP0;
uint32_t letimer0_comp1 = COMP1;


/* Name: calculate_LETIMER_LFXOPrescaler()
 * Routine to calculate the low frequency prescaler for the LETIMER
 * clocked with LFXO based on the desired period.
 *
 * Input variables: desired_period - desired timing period in seconds
 * Global variables: none used
 * Returned variables: div - clock divisor to use
 *
 */
uint32_t calculate_LETIMER_LFXOPrescaler(uint32_t desired_period)
{
    uint32_t max_period = LETIMER0_LFXO_DEFAULT_MAX_PERIOD;
    uint32_t div = 1;
    while ((max_period < OPERATING_PERIOD) && (div < LETIMER0_CMU_LFAPRESC0_MAX_DIV))
    {
        div <<= 1;
        max_period <<= 1;
    }
    return div;
}

void letimer_Setup(void)
{
#if LOWEST_ENERGY_MODE_ALLOWED == EM2
    uint32_t LFXO_divisor;
    LFXO_divisor = calculate_LETIMER_LFXOPrescaler(OPERATING_PERIOD);//calculate prescaler
    CMU_ClockDivSet(cmuClock_LETIMER0, LFXO_divisor);
    letimer0_comp0 /= LFXO_divisor;
    letimer0_comp1 /= LFXO_divisor;
#endif

    const LETIMER_Init_TypeDef letimer_Config =
    {
        .enable         = false,                  // Start counting when init completed.
        .debugRun       = false,                  // Counter shall not keep running during debug halt.
        .rtcComp0Enable = false,                  // Don't start counting on RTC COMP0 match.
        .rtcComp1Enable = false,                  // Don't start counting on RTC COMP1 match.
        .comp0Top       = true,                   // Load COMP0 register into CNT when counter underflows. COMP0 is used as TOP
        .bufTop         = false,                  // Don't load COMP1 into COMP0 when REP0 reaches 0.
        .out0Pol        = 0,                      // Idle value for output 0.
        .out1Pol        = 0,                      // Idle value for output 1.
        .ufoa0          = letimerUFOANone,        // No output actions
        .ufoa1          = letimerUFOANone,        // No output actions
        .repMode        = letimerRepeatFree       // Count until stopped
    };

    /* Initialize LETIMER0 */
    LETIMER_Init(LETIMER0, &letimer_Config);

    /* Set initial compare values for COMP0 and COMP1 */
    LETIMER_CompareSet(LETIMER0, 0, letimer0_comp0);
    LETIMER_CompareSet(LETIMER0, 1, letimer0_comp1);
    /* Enable the LETIMER0's COMP0 and COMP1 interrupt */
    LETIMER_IntClear(LETIMER0, _LETIMER_IFC_MASK);
    LETIMER_IntEnable(LETIMER0, LETIMER_IEN_COMP0);
    LETIMER_IntEnable(LETIMER0, LETIMER_IEN_COMP1);
    NVIC_EnableIRQ(LETIMER0_IRQn);
}

