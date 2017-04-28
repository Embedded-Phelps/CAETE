/*
 * serial_BLE.c
 *
 *  Created on: Apr 20, 2017
 *      Author: shuting
 */

#include "LG_system.h"

uint8_t ble_Transmit_Buff[TX_BUFFER_SIZE][DATA_MAX_LEN];
static uint32_t tx_buffer_write_ptr = TX_BUFFER_SIZE - 1;
static uint32_t tx_buffer_transmit_ptr = TX_BUFFER_SIZE -1;

bool data_transmitting_flag = false;


void serial_BLE(void)
{
	uint32_t str_length;
	uint8_t *str_ptr;
    data_transmitting_flag = true;
    tx_buffer_transmit_ptr++;
    tx_buffer_transmit_ptr %= TX_BUFFER_SIZE;
    str_length = strlen(ble_Transmit_Buff[tx_buffer_transmit_ptr]);
    str_ptr = ble_Transmit_Buff[tx_buffer_transmit_ptr];
    LEUART0->CTRL |= LEUART_CTRL_TXDMAWU;
    //DMA_ENABLE();
    blockSleepMode(DMA_EM);
    DMA_ActivateBasic(LEUART0_TX_DMA_CHANNEL, true, false, (void *)&(LEUART0->TXDATA), (void *)str_ptr, str_length-1);

}

void serial_PreparePacket(packet_type_e packet_id, void *value, uint8_t *packet, uint8_t *len)
{

	switch(packet_id)
	{
	case TEMPERATURE:
		packet[0] = DATA_TYPE | TEMPERATURE;
		packet[1] = (uint8_t)(*(double*)value);
		packet[2] = (uint8_t)((*(double*)value - packet[1])*100);
		*len = 3;
		break;
	case BAROMETRIC_PRESSURE:
		packet[0] = DATA_TYPE | BAROMETRIC_PRESSURE;
		packet[1] = (uint8_t)(*(double*)value/1000);
		packet[2] = (uint8_t)((*(double*)value/1000 - packet[1])*100);
		len = 3;
		break;
	case MOTION:
		packet[0] = STATE_TYPE | MOTION;
		packet[1] = *(uint8_t *)value;
		*len = 2;
		break;
	case AMBIENT_LIGHT:
		packet[0] = STATE_TYPE | AMBIENT_LIGHT;
		packet[1] = *(uint8_t *)value;
		*len = 2;
		break;
	case CAP_TOUCHED:
		packet[0] = STATE_TYPE | CAP_TOUCHED;
		packet[1] = *(uint8_t *)value;
		*len = 2;
		break;
	default:
		break;
	}
}

void serial_SendPacket(packet_type_e packet_id, void * value)
{
	uint8_t outstring[DATA_MAX_LEN] = {0};
	uint8_t len;

	CORE_CriticalDisableIrq();
	serial_PreparePacket(packet_id, value, outstring, &len);
    tx_buffer_write_ptr++;
    tx_buffer_write_ptr %= TX_BUFFER_SIZE;
    strncpy(ble_Transmit_Buff[tx_buffer_write_ptr], "", DATA_MAX_LEN);
    strncpy(ble_Transmit_Buff[tx_buffer_write_ptr], outstring, len);
    if(!data_transmitting_flag)
    {
    	serial_BLE();
    }
    CORE_CriticalEnableIrq();
}

void serial_TXTransferDoneCB(uint8_t channel, bool primary, void *user)
{
    CORE_CriticalDisableIrq();
    DMA->IFC = 1 << channel;
    LEUART0->CTRL &= ~LEUART_CTRL_TXDMAWU;
    unblockSleepMode(DMA_EM);
    //DMA_DISABLE();
    strncpy(ble_Transmit_Buff[tx_buffer_transmit_ptr], "", DATA_MAX_LEN);
    data_transmitting_flag = false;
    if(tx_buffer_transmit_ptr != tx_buffer_write_ptr)
    {
    	serial_BLE();
    }
    CORE_CriticalEnableIrq();
}

void serial_RXTransferDoneCB(uint8_t channel, bool primary, void *user)
{
	CORE_CriticalDisableIrq();
	DMA->IFC = 1 << channel;
	DMA_ActivateBasic(LEUART0_RX_DMA_CHANNEL, true, false, (void *)&data_upload_flag, (void *)&(LEUART0->RXDATA), LEUART_RECEIVE_LENGTH-1);
	CORE_CriticalEnableIrq();
}
