#include "task_adc.h"

#include "adc_manager.h"
#include "hall_sensor.h"
#include "battery_monitor.h"
#include "watchdog_manager.h"

void Task_ADC_Run(void)
{
    ADC_Manager_Update();

    HallSensor_Update(
        ADC_GetSpoolRaw(),
        ADC_GetKneeRaw());

    BatteryMonitor_Update(
        ADC_GetBatteryRaw());

    WatchdogManager_KickTask(
        WDG_TASK_ADC);
}
