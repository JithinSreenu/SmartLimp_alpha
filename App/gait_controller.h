#ifndef GAIT_CONTROLLER_H
#define GAIT_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "protocol_config.h"
#include "shared_types.h"

/*=========================================================
 * Gait Command Structure
 *=========================================================*/
typedef struct
{
    uint8_t valveOpenPercent;

    uint16_t pwmDuty;

    bool motorOpenCmd;

    bool motorCloseCmd;

} GaitCommand_t;

/*=========================================================
 * Public Functions
 *=========================================================*/

void GaitController_Init(void);

void GaitController_Update(
        SystemState_t currentState,
        const SensorData_t *sensorData);

GaitCommand_t GaitController_GetCommand(void);

#ifdef __cplusplus
}
#endif

#endif
