#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "shared_types.h"
#include "protocol_config.h"

/*=========================================================
 * Public Functions
 *=========================================================*/

/**
 * @brief Initialize state machine
 */
void StateMachine_Init(void);

/**
 * @brief Update state machine
 *
 * @param sensorData Sensor inputs
 */
void StateMachine_Update(
        const SensorData_t *sensorData);

/**
 * @brief Get current state
 *
 * @return Current system state
 */
SystemState_t StateMachine_GetState(void);

/**
 * @brief Force state transition
 *
 * @param state New state
 */
void StateMachine_SetState(
        SystemState_t state);

/**
 * @brief Check if fault state active
 *
 * @return true if fault
 */
bool StateMachine_IsFault(void);

#ifdef __cplusplus
}
#endif

#endif
