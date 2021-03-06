/*
 * LG_leuart.c
 *
 *  Created on: Apr 20, 2017
 *      Author: shuting
 */


#include "LG_System.h"

DMA_CB_TypeDef dma_LEUART0_Tx_Callback;
DMA_CB_TypeDef dma_LEUART0_Rx_Callback;

void leuart_Setup(void);
static void leuart_DMASetup(void);

/**************************************************************************
 *	@brief  LEUART modules setup function
 **************************************************************************/
void leuart_Setup(void)
{
	CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
	/* Defining the LEUART0 initialization data */
	LEUART_Init_TypeDef leuart0_Config =
	{
	  .enable   = LEUART0_ENABLE,       /* Activate data transmission on LEUn_TX pin. */
	  .refFreq  = 0,                    /* Use the currently configurated reference clock */
	  .baudrate = LEUART0_BAUDRATE,     /* Baudrate setting: 9600 */
	  .databits = LEUART0_DATABITS,     /* Each LEUART frame containes 8 databits */
	  .parity   = LEUART0_PARITY,       /* No parity bits in use */
	  .stopbits = LEUART0_STOPBIT,      /* Setting the number of stop bits in a frame to 1 bitperiods */
	};

    GPIO_PinModeSet(LEUART0_TX_PORT, LEUART0_TX_PIN, gpioModePushPull, 1);
    GPIO_PinModeSet(LEUART0_RX_PORT, LEUART0_RX_PIN, gpioModeInputPull, 0);

	/* Reseting and initializing LEUART1 */
	LEUART_Reset(LEUART0);
	LEUART_Init(LEUART0, &leuart0_Config);

	/* Route LEUART0 TX pin to location 0 */
	LEUART0->ROUTE = LEUART_ROUTE_TXPEN | LEUART_ROUTE_RXPEN | LEUART0_ROUTE_LOC;
	leuart_DMASetup();

	LEUART0->CTRL |= LEUART_CTRL_RXDMAWU;
	DMA_ENABLE();
	DMA_ActivateBasic(LEUART0_RX_DMA_CHANNEL, true, false, (void *)&data_upload_flag, (void *)&(LEUART0->RXDATA), LEUART_RECEIVE_LENGTH-1);
}

static void leuart_DMASetup(void)
{
    dma_LEUART0_Tx_Callback.cbFunc = serial_TXTransferDoneCB;
    dma_LEUART0_Tx_Callback.userPtr = NULL;
    dma_LEUART0_Tx_Callback.primary = 0;

    dma_LEUART0_Rx_Callback.cbFunc = serial_RXTransferDoneCB;
    dma_LEUART0_Rx_Callback.userPtr = NULL;
    dma_LEUART0_Rx_Callback.primary = 0;

    DMA_Init_TypeDef dma_Config =
    {
        .hprot = 0,
        .controlBlock = dmaControlBlock,
    };

    DMA_CfgDescr_TypeDef tx_Descr_Config =
    {
        .dstInc = dmaDataIncNone,
        .srcInc = dmaDataInc1,
        .size = dmaDataSize1,
        .arbRate = dmaArbitrate1,
        .hprot = 0
    };

    DMA_CfgChannel_TypeDef tx_Chn_Config =
    {
        .highPri = false,
        .enableInt = true,
        .select = DMAREQ_LEUART0_TXEMPTY,
        .cb = &dma_LEUART0_Tx_Callback
    };

    DMA_CfgDescr_TypeDef rx_Descr_Config =
    {
        .dstInc = dmaDataInc1,
        .srcInc = dmaDataIncNone,
        .size = dmaDataSize1,
        .arbRate = dmaArbitrate1,
        .hprot = 0
    };

    DMA_CfgChannel_TypeDef rx_Chn_Config =
    {
        .highPri = false,
        .enableInt = true,
        .select = DMAREQ_LEUART0_RXDATAV,
        .cb = &dma_LEUART0_Rx_Callback
    };

    /* Configure general DMA issues */
    DMA_Init(&dma_Config);

    /* Configure DMA channel used */
    DMA_CfgChannel(LEUART0_TX_DMA_CHANNEL, &tx_Chn_Config);
    DMA_CfgChannel(LEUART0_RX_DMA_CHANNEL, &rx_Chn_Config);
    DMA_CfgDescr(LEUART0_TX_DMA_CHANNEL, true, &tx_Descr_Config);
    DMA_CfgDescr(LEUART0_RX_DMA_CHANNEL, true, &rx_Descr_Config);
    DMA->IEN |= 6;

    NVIC_EnableIRQ(DMA_IRQn);
}
