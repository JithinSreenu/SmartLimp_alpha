#include "task_bluetooth.h"

#include "bluetooth.h"
#include "state_machine.h"
#include "shared_types.h"
#include "watchdog_manager.h"

extern SensorData_t gSensorData;

void Task_Bluetooth_Run(void)
{
    Telemetry_t telemetry;

    telemetry.spoolAngle =
        gSensorData.spoolAngle;

    telemetry.force =
        gSensorData.force;

    telemetry.kneeAngle =
        gSensorData.kneeAngle;

    telemetry.moment =
        gSensorData.moment;

    telemetry.stateID =
        StateMachine_GetState();

    telemetry.battery_mV =
        gSensorData.battery_mV;

    Bluetooth_SendTelemetry(
        &telemetry);

    Bluetooth_Update();

    WatchdogManager_KickTask(
        WDG_TASK_BLUETOOTH);
}
