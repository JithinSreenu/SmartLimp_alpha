#include "task_motor.h"

#include "gait_controller.h"
#include "motor_control.h"
#include "state_machine.h"
#include "watchdog_manager.h"

void Task_Motor_Run(void)
{
    GaitController_Update(
        StateMachine_GetState(),
        NULL);

    GaitCommand_t cmd =
        GaitController_GetCommand();

    MotorControl_Update(
        &cmd);

    WatchdogManager_KickTask(
        WDG_TASK_MOTOR);
}
