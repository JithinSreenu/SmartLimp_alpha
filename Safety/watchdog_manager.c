#include "watchdog_manager.h"

#include <string.h>

#include "iwdg.h"
#include "fault_manager.h"

/*=========================================================
 * Configuration
 *=========================================================*/

#define TASK_TIMEOUT_COUNT     10U

/*=========================================================
 * Private Variables
 *=========================================================*/

static uint16_t taskCounters[WDG_TASK_COUNT];

static bool watchdogHealthy;

/*=========================================================
 * Initialize
 *=========================================================*/

void WatchdogManager_Init(void)
{
    memset(taskCounters,
           0,
           sizeof(taskCounters));

    watchdogHealthy = true;
}

/*=========================================================
 * Task Heartbeat
 *=========================================================*/

void WatchdogManager_KickTask(
        WatchdogTask_t task)
{
    if(task >= WDG_TASK_COUNT)
    {
        return;
    }

    taskCounters[task] = 0;
}

/*=========================================================
 * Update
 *=========================================================*/

void WatchdogManager_Update(void)
{
    uint32_t i;

    for(i = 0;
        i < WDG_TASK_COUNT;
        i++)
    {
        taskCounters[i]++;

        if(taskCounters[i] >
           TASK_TIMEOUT_COUNT)
        {
            watchdogHealthy = false;

            FaultManager_SetFault(
                FAULT_WATCHDOG);

            return;
        }
    }

    HAL_IWDG_Refresh(&hiwdg);
}

/*=========================================================
 * Health Status
 *=========================================================*/

bool WatchdogManager_IsHealthy(void)
{
    return watchdogHealthy;
}
