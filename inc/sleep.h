//===============================================================================
// File: sleep.h
// Sleep APIs header file
//
// Author: ShuTing Guo
// Date: 01/31/2017
//===============================================================================

#ifndef INC_SLEEP_H_
#define INC_SLEEP_H_

/**********************************************************************/
/* Name: blockSleepMode()
 * Routine to block the microcontroller from sleeping below a certain mode
 *
 * Input variables: lowest_Energymode specifies the lowest energy mode allowed
 * Global variables: sleep_block_counter[] is used to update current lowest energy mode.
 * Returned variables: none defined
 *
 */
void blockSleepMode(int32_t lowest_Energymode);

/**********************************************************************/
/* Name: unblockSleepMode()
 * Routine to unblock the microcontroller from sleeping below a certain mode
 *
 * Input variables: lowest_Energymode specifies the lowest energy mode allowed
 * Global variables: sleep_block_counter[] is used to update current lowest energy mode.
 * Returned variables: none defined
 *
 */
void unblockSleepMode(int32_t lowest_Energymode);

/**********************************************************************/
/* Name: Sleep()
 * Routine to enter the lowest energy mode allowed
 *
 * Input variables: none defined
 * Global variables: sleep_block_counter[] is used to determine the lowest energy mode allowed.
 * Returned variables: none defined
 *
 */
void sleep(void);

#endif /* INC_SLEEP_H_ */
