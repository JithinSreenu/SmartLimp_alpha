#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*=========================================================
 * Battery Status
 *=========================================================*/
typedef enum
{
    BATTERY_STATUS_CRITICAL = 0,

    BATTERY_STATUS_LOW,

    BATTERY_STATUS_NORMAL,

    BATTERY_STATUS_FULL

} BatteryStatus_t;

/*=========================================================
 * Public Functions
 *=========================================================*/

void BatteryMonitor_Init(void);

void BatteryMonitor_Update(uint16_t adcValue);

uint16_t BatteryMonitor_GetVoltage_mV(void);

uint8_t BatteryMonitor_GetPercentage(void);

BatteryStatus_t BatteryMonitor_GetStatus(void);

bool BatteryMonitor_IsHealthy(void);

#ifdef __cplusplus
}
#endif

#endif
