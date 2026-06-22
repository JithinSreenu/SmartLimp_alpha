#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "shared_types.h"
#include "protocol_config.h"

/*=========================================================
 * Public Functions
 *=========================================================*/

void Bluetooth_Init(void);

void Bluetooth_Update(void);

bool Bluetooth_SendTelemetry(
        const Telemetry_t *telemetry);

void Bluetooth_ProcessRx(void);

bool Bluetooth_IsConnected(void);

CommandID_t Bluetooth_GetLastCommand(void);

#ifdef __cplusplus
}
#endif

#endif
