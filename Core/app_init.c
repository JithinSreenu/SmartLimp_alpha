#include "app_init.h"

/* Drivers */
#include "adc_manager.h"
#include "hall_sensor.h"
#include "battery_monitor.h"
#include "motor_control.h"

/* Filters */
#include "moving_average.h"
#include "iir_filter.h"

/* Application */
#include "force_estimator.h"
#include "moment_estimator.h"
#include "gait_controller.h"

/* State Machine */
#include "state_machine.h"

/* Safety */
#include "fault_manager.h"
#include "watchdog_manager.h"

/* Communication */
#include "bluetooth.h"

/*=========================================================
 * Application Initialization
 *=========================================================*/

void App_Init(void)
{

    RTOS_Queues_Init();
    /* Safety First */
    FaultManager_Init();

    WatchdogManager_Init();

    /* Drivers */
    ADC_Manager_Init();

    HallSensor_Init();

    BatteryMonitor_Init();

    MotorControl_Init();

    /* Filters */

    /* Application */

    ForceEstimator_Init();

    MomentEstimator_Init();

    /* State Machine */

    StateMachine_Init();

    /* Control */

    GaitController_Init();

    /* Communication */

    Bluetooth_Init();

    /* Start ADC DMA */

    ADC_Manager_Start();
}
