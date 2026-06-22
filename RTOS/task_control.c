#include "task_control.h"

#include "force_estimator.h"
#include "moment_estimator.h"
#include "state_machine.h"
#include "hall_sensor.h"
#include "shared_types.h"
#include "watchdog_manager.h"

static SensorData_t sensorData;

void Task_Control_Run(void)
{
    sensorData.force =
        ForceEstimator_GetForce();

    sensorData.kneeAngle =
        HallSensor_GetKneeAngle();

    sensorData.spoolAngle =
        HallSensor_GetSpoolAngle();

    MomentEstimator_Update(
        sensorData.force);

    sensorData.moment =
        MomentEstimator_GetMoment();

    sensorData.battery_mV =
        BatteryMonitor_GetVoltage_mV();

    StateMachine_Update(
        &sensorData);

    WatchdogManager_KickTask(
        WDG_TASK_CONTROL);
}
