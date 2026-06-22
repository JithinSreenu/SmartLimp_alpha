#ifndef RTOS_QUEUES_H
#define RTOS_QUEUES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "queue.h"

#include "shared_types.h"

/*=========================================================
 * Global Queue Handles
 *=========================================================*/

extern QueueHandle_t sensorQueue;

extern QueueHandle_t telemetryQueue;

extern QueueHandle_t commandQueue;

extern QueueHandle_t faultQueue;

/*=========================================================
 * Functions
 *=========================================================*/

void RTOS_Queues_Init(void);

#ifdef __cplusplus
}
#endif

#endif
