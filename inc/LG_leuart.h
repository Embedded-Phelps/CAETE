/*
 * LG_leuart.h
 *
 *  Created on: Apr 20, 2017
 *      Author: shuting
 */

#ifndef INC_LG_LEUART_H_
#define INC_LG_LEUART_H_

#define LEUART0_TX_DMA_CHANNEL	(1)

#define DMA_DISABLE()			(DMA->CONFIG &= ~DMA_CONFIG_EN)
#define DMA_ENABLE()			(DMA->CONFIG |= DMA_CONFIG_EN)

void leuart_Setup(void);

#endif /* INC_LG_LEUART_H_ */
