#include "gait_controller.h"

#include <string.h>

/*=========================================================
 * Private Variables
 *=========================================================*/

static GaitCommand_t gaitCommand;

/*=========================================================
 * Private Functions
 *=========================================================*/

static void HandleIdleState(void);
static void HandleStandingState(void);
static void HandleWalkingState(
        const SensorData_t *sensorData);
static void HandleSittingState(void);
static void HandleStairAscentState(void);
static void HandleStairDescentState(void);
static void HandleFaultState(void);

/*=========================================================
 * Initialize
 *=========================================================*/

void GaitController_Init(void)
{
    memset(&gaitCommand,
           0,
           sizeof(gaitCommand));
}

/*=========================================================
 * Update
 *=========================================================*/

void GaitController_Update(
        SystemState_t currentState,
        const SensorData_t *sensorData)
{
    switch(currentState)
    {
        case STATE_IDLE:
            HandleIdleState();
            break;

        case STATE_STANDING:
            HandleStandingState();
            break;

        case STATE_WALKING:
            HandleWalkingState(sensorData);
            break;

        case STATE_SITTING:
            HandleSittingState();
            break;

        case STATE_STAIR_ASCENT:
            HandleStairAscentState();
            break;

        case STATE_STAIR_DESCENT:
            HandleStairDescentState();
            break;

        case STATE_FAULT:
            HandleFaultState();
            break;

        default:
            HandleFaultState();
            break;
    }
}

/*=========================================================
 * IDLE
 *=========================================================*/

static void HandleIdleState(void)
{
    gaitCommand.valveOpenPercent = 0;

    gaitCommand.pwmDuty = 0;

    gaitCommand.motorOpenCmd = false;

    gaitCommand.motorCloseCmd = false;
}

/*=========================================================
 * STANDING
 *=========================================================*/

static void HandleStandingState(void)
{
    /*
     * Maximum support
     */

    gaitCommand.valveOpenPercent = 0;

    gaitCommand.pwmDuty = 900;

    gaitCommand.motorOpenCmd = false;

    gaitCommand.motorCloseCmd = true;
}

/*=========================================================
 * WALKING
 *=========================================================*/

static void HandleWalkingState(
        const SensorData_t *sensorData)
{
    uint16_t pwm;

    if(sensorData == NULL)
    {
        return;
    }

    /*
     * Adaptive damping
     */

    pwm = 300;

    if(sensorData->force > 100)
    {
        pwm = 600;
    }

    gaitCommand.valveOpenPercent = 40;

    gaitCommand.pwmDuty = pwm;

    gaitCommand.motorOpenCmd = true;

    gaitCommand.motorCloseCmd = false;
}

/*=========================================================
 * SITTING
 *=========================================================*/

static void HandleSittingState(void)
{
    gaitCommand.valveOpenPercent = 20;

    gaitCommand.pwmDuty = 250;

    gaitCommand.motorOpenCmd = true;

    gaitCommand.motorCloseCmd = false;
}

/*=========================================================
 * STAIR ASCENT
 *=========================================================*/

static void HandleStairAscentState(void)
{
    gaitCommand.valveOpenPercent = 60;

    gaitCommand.pwmDuty = 700;

    gaitCommand.motorOpenCmd = true;

    gaitCommand.motorCloseCmd = false;
}

/*=========================================================
 * STAIR DESCENT
 *=========================================================*/

static void HandleStairDescentState(void)
{
    gaitCommand.valveOpenPercent = 30;

    gaitCommand.pwmDuty = 400;

    gaitCommand.motorOpenCmd = true;

    gaitCommand.motorCloseCmd = false;
}

/*=========================================================
 * FAULT
 *=========================================================*/

static void HandleFaultState(void)
{
    /*
     * Safe State
     *
     * Close hydraulic valve
     * Disable motion
     */

    gaitCommand.valveOpenPercent = 0;

    gaitCommand.pwmDuty = 0;

    gaitCommand.motorOpenCmd = false;

    gaitCommand.motorCloseCmd = false;
}

/*=========================================================
 * Get Command
 *=========================================================*/

GaitCommand_t GaitController_GetCommand(void)
{
    return gaitCommand;
}
