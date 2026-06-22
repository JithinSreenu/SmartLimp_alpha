#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "protocol_config.h"

/*=========================================================
 * Public Functions
 *=========================================================*/

void FaultManager_Init(void);

void FaultManager_SetFault(
        FaultCode_t faultCode);

void FaultManager_ClearFault(void);

FaultCode_t FaultManager_GetFault(void);

bool FaultManager_IsFaultActive(void);

void FaultManager_Update(void);

#ifdef __cplusplus
}
#endif

#endif
