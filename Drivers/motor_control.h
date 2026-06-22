#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "gait_controller.h"

/*=========================================================
 * Motor State
 *=========================================================*/
typedef enum
{
    MOTOR_STOPPED = 0,

    MOTOR_OPENING,

    MOTOR_CLOSING

} MotorState_t;

/*=========================================================
 * Public Functions
 *=========================================================*/

void MotorControl_Init(void);

void MotorControl_Update(
        const GaitCommand_t *command);

void MotorControl_Stop(void);

void MotorControl_OpenValve(
        uint16_t pwmDuty);

void MotorControl_CloseValve(
        uint16_t pwmDuty);

MotorState_t MotorControl_GetState(void);

bool MotorControl_IsHealthy(void);

#ifdef __cplusplus
}
#endif

#endif
