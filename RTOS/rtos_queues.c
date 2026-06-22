#include "rtos_queues.h"

/*=========================================================
 * Queue Handles
 *=========================================================*/

QueueHandle_t sensorQueue;

QueueHandle_t telemetryQueue;

QueueHandle_t commandQueue;

QueueHandle_t faultQueue;

/*=========================================================
 * Queue Creation
 *=========================================================*/

void RTOS_Queues_Init(void)
{
    sensorQueue =
        xQueueCreate(
            8,
            sizeof(SensorData_t));

    telemetryQueue =
        xQueueCreate(
            8,
            sizeof(Telemetry_t));

    commandQueue =
        xQueueCreate(
            8,
            sizeof(CommandPacket_t));

    faultQueue =
        xQueueCreate(
            8,
            sizeof(FaultData_t));
}
