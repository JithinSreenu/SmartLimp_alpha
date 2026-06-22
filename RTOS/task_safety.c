#include "fault_manager.h"
#include "watchdog_manager.h"
#include "adc_manager.h"

void Task_Safety_Run(void)
{
    if(!ADC_IsHealthy())
    {
        FaultManager_SetFault(
            FAULT_ADC);
    }

    WatchdogManager_KickTask(
        WDG_TASK_SAFETY);
}
