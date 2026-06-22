#ifndef WATCHDOG_MANAGER_H
#define WATCHDOG_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/*=========================================================
 * Task Monitoring IDs
 *=========================================================*/
typedef enum
{
    WDG_TASK_ADC = 0,

    WDG_TASK_CONTROL,

    WDG_TASK_MOTOR,

    WDG_TASK_BLUETOOTH,

    WDG_TASK_SAFETY,

    WDG_TASK_COUNT

} WatchdogTask_t;

/*=========================================================
 * Public Functions
 *=========================================================*/

void WatchdogManager_Init(void);

void WatchdogManager_KickTask(
        WatchdogTask_t task);

void WatchdogManager_Update(void);

bool WatchdogManager_IsHealthy(void);

#ifdef __cplusplus
}
#endif

#endif
