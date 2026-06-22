#ifndef UART_DMA_H
#define UART_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define UART_RX_BUFFER_SIZE    256U
#define UART_TX_BUFFER_SIZE    256U

void UART_DMA_Init(void);

void UART_DMA_StartReception(void);

bool UART_DMA_Transmit(
        const uint8_t *data,
        uint16_t length);

uint16_t UART_DMA_GetRxData(
        uint8_t *buffer,
        uint16_t maxLength);

bool UART_DMA_IsTxBusy(void);

void UART_DMA_RxEventCallback(
        uint16_t size);

void UART_DMA_TxCompleteCallback(void);

#ifdef __cplusplus
}
#endif

#endif
