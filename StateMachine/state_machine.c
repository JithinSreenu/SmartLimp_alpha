#include "state_machine.h"

#include "sensor_config.h"

/*=========================================================
 * Private Variables
 *=========================================================*/

static SystemState_t currentState;

/*=========================================================
 * Private Functions
 *=========================================================*/

static void EvaluateIdle(
        const SensorData_t *sensor);

static void EvaluateStanding(
        const SensorData_t *sensor);

static void EvaluateWalking(
        const SensorData_t *sensor);

static void EvaluateSitting(
        const SensorData_t *sensor);

/*=========================================================
 * Initialize
 *=========================================================*/

void StateMachine_Init(void)
{
    currentState = STATE_IDLE;
}

/*=========================================================
 * Update
 *=========================================================*/

void StateMachine_Update(
        const SensorData_t *sensor)
{
    if(sensor == NULL)
    {
        return;
    }

    switch(currentState)
    {
        case STATE_IDLE:
            EvaluateIdle(sensor);
            break;

        case STATE_STANDING:
            EvaluateStanding(sensor);
            break;

        case STATE_WALKING:
            EvaluateWalking(sensor);
            break;

        case STATE_SITTING:
            EvaluateSitting(sensor);
            break;

        case STATE_STAIR_ASCENT:
            break;

        case STATE_STAIR_DESCENT:
            break;

        case STATE_CALIBRATION:
            break;

        case STATE_FAULT:
            break;

        default:
            currentState = STATE_FAULT;
            break;
    }
}

/*=========================================================
 * IDLE State
 *=========================================================*/

static void EvaluateIdle(
        const SensorData_t *sensor)
{
    if(sensor->force >
       STANDING_FORCE_THRESHOLD)
    {
        currentState =
            STATE_STANDING;
    }
}

/*=========================================================
 * STANDING State
 *=========================================================*/

static void EvaluateStanding(
        const SensorData_t *sensor)
{
    if(sensor->kneeAngle >
       SITTING_KNEE_ANGLE_THRESHOLD)
    {
        currentState =
            STATE_SITTING;

        return;
    }

    if(sensor->spoolAngle > 10)
    {
        currentState =
            STATE_WALKING;

        return;
    }
}

/*=========================================================
 * WALKING State
 *=========================================================*/

static void EvaluateWalking(
        const SensorData_t *sensor)
{
    if(sensor->force <
       WALKING_FORCE_THRESHOLD)
    {
        currentState =
            STATE_IDLE;

        return;
    }

    if(sensor->kneeAngle >
       SITTING_KNEE_ANGLE_THRESHOLD)
    {
        currentState =
            STATE_SITTING;

        return;
    }
}

/*=========================================================
 * SITTING State
 *=========================================================*/

static void EvaluateSitting(
        const SensorData_t *sensor)
{
    if(sensor->kneeAngle < 30)
    {
        currentState =
            STATE_STANDING;
    }
}

/*=========================================================
 * Get State
 *=========================================================*/

SystemState_t StateMachine_GetState(void)
{
    return currentState;
}

/*=========================================================
 * Set State
 *=========================================================*/

void StateMachine_SetState(
        SystemState_t state)
{
    currentState = state;
}

/*=========================================================
 * Fault Check
 *=========================================================*/

bool StateMachine_IsFault(void)
{
    return (currentState ==
            STATE_FAULT);
}
