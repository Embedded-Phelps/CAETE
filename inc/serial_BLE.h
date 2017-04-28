/*
 * serial_BLE.h
 *
 *  Created on: Apr 20, 2017
 *      Author: shuting
 */

#ifndef INC_SERIAL_BLE_H_
#define INC_SERIAL_BLE_H_

#define TX_BUFFER_SIZE		(20)
#define DATA_MAX_LEN		(20)

#define DATA_TYPE			(0x00U)
#define STATE_TYPE			(0x80U)

typedef enum
{
	TEMPERATURE = 2U,
	BAROMETRIC_PRESSURE,

	MOTION,
	AMBIENT_LIGHT,
	CAP_TOUCHED
}packet_type_e;

#define TURN_ON		(1)
#define TURN_OFF	(2)

#define MOTION_DETECTED		(1)
#define NO_MOTION_DETECTED	(2)


void serial_SendPacket(packet_type_e packet_id, void * value);
extern void serial_TXTransferDoneCB(uint8_t channel, bool primary, void *user);

#endif /* INC_SERIAL_BLE_H_ */
