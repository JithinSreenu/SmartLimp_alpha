#include "uart_dma.h"

#include <string.h>

#include "usart.h"

static uint8_t rxBuffer[UART_RX_BUFFER_SIZE];

static uint8_t txBuffer[UART_TX_BUFFER_SIZE];

static volatile uint16_t rxLength;

static volatile bool txBusy;

/*=========================================================
 * Initialize
 *=========================================================*/

void UART_DMA_Init(void)
{
    rxLength = 0;

    txBusy = false;
}

/*=========================================================
 * Start Reception
 *=========================================================*/

void UART_DMA_StartReception(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(
            &huart1,
            rxBuffer,
            UART_RX_BUFFER_SIZE);

    __HAL_DMA_DISABLE_IT(
            huart1.hdmarx,
            DMA_IT_HT);
}

/*=========================================================
 * Transmit
 *=========================================================*/

bool UART_DMA_Transmit(
        const uint8_t *data,
        uint16_t length)
{
    if(txBusy)
    {
        return false;
    }

    if(length > UART_TX_BUFFER_SIZE)
    {
        return false;
    }

    memcpy(txBuffer,
           data,
           length);

    txBusy = true;

    HAL_UART_Transmit_DMA(
            &huart1,
            txBuffer,
            length);

    return true;
}

/*=========================================================
 * Get RX Data
 *=========================================================*/

uint16_t UART_DMA_GetRxData(
        uint8_t *buffer,
        uint16_t maxLength)
{
    uint16_t copyLength;

    copyLength = rxLength;

    if(copyLength > maxLength)
    {
        copyLength = maxLength;
    }

    memcpy(buffer,
           rxBuffer,
           copyLength);

    rxLength = 0;

    return copyLength;
}

/*=========================================================
 * TX Status
 *=========================================================*/

bool UART_DMA_IsTxBusy(void)
{
    return txBusy;
}

/*=========================================================
 * RX Callback
 *=========================================================*/

void UART_DMA_RxEventCallback(
        uint16_t size)
{
    rxLength = size;

    HAL_UARTEx_ReceiveToIdle_DMA(
            &huart1,
            rxBuffer,
            UART_RX_BUFFER_SIZE);

    __HAL_DMA_DISABLE_IT(
            huart1.hdmarx,
            DMA_IT_HT);
}

/*=========================================================
 * TX Complete
 *=========================================================*/

void UART_DMA_TxCompleteCallback(void)
{
    txBusy = false;
}
