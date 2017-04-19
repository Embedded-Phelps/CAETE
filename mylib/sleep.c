//===============================================================================
// File: sleep.c
// Sleep APIs
//
// Author: ShuTing Guo
// Date: 01/31/2017
//===============================================================================

#include "LG_system.h"
/*******************************************************************************
 ****************************  Global Variables  *******************************
 ******************************************************************************/

uint8_t sleep_block_counter[3] = {0}; // Counts the lowest possible active states


/*******************************************************************************
 ****************************  Global Functions  *******************************
 ******************************************************************************/

/**********************************************************************/
/* Name: blockSleepMode()
 * Routine to block the microcontroller from sleeping below a certain mode
 *
 * Input variables: lowest_Energymode specifies the lowest energy mode allowed
 * Global variables: sleep_block_counter[] is used to update current lowest energy mode.
 * Returned variables: none defined
 *
 */
void blockSleepMode(int32_t lowest_Energymode)
{
	CORE_CriticalDisableIrq();
	sleep_block_counter[lowest_Energymode]++;
	CORE_CriticalEnableIrq();
}

/**********************************************************************/
/* Name: unblockSleepMode()
 * Routine to unblock the microcontroller from sleeping below a certain mode
 *
 * Input variables: lowest_Energymode specifies the lowest energy mode allowed
 * Global variables: sleep_block_counter[] is used to update current lowest energy mode.
 * Returned variables: none defined
 *
 */
void unblockSleepMode(int32_t lowest_Energymode)
{
	CORE_CriticalDisableIrq();
	if(sleep_block_counter[lowest_Energymode]>0)
	{
		sleep_block_counter[lowest_Energymode]--;
	}
	CORE_CriticalEnableIrq();
}

/**********************************************************************/
/* Name: Sleep()
 * Routine to enter the lowest energy mode allowed
 *
 * Input variables: none defined
 * Global variables: sleep_block_counter[] is used to determine the lowest energy mode allowed.
 * Returned variables: none defined
 *
 */
void sleep(void)
{
	if(sleep_block_counter[0]>0)			// Energy mode below EM0 is blocked
	{
		return;
	}
	else if(sleep_block_counter[1]>0)		// Energy mode below EM1 is blocked
	{
		EMU_EnterEM1();
	}
	else if(sleep_block_counter[2]>0)		// Energy mode below EM2 is blocked
	{
		EMU_EnterEM2(true);
	}
	else if(sleep_block_counter[3]>0)		// Energy mode below EM4 is blocked
	{
		EMU_EnterEM3(true);
	}
	else									// nothing is blocked
	{
		EMU_EnterEM3(true);
	}

}
