#include "fault_manager.h"

#include "state_machine.h"

static FaultCode_t currentFault;

static bool faultActive;

/*=========================================================
 * Initialize
 *=========================================================*/

void FaultManager_Init(void)
{
    currentFault = FAULT_NONE;

    faultActive = false;
}

/*=========================================================
 * Set Fault
 *=========================================================*/

void FaultManager_SetFault(
        FaultCode_t faultCode)
{
    currentFault = faultCode;

    faultActive = true;

    StateMachine_SetState(
            STATE_FAULT);
}

/*=========================================================
 * Clear Fault
 *=========================================================*/

void FaultManager_ClearFault(void)
{
    currentFault = FAULT_NONE;

    faultActive = false;

    StateMachine_SetState(
            STATE_IDLE);
}

/*=========================================================
 * Get Fault
 *=========================================================*/

FaultCode_t FaultManager_GetFault(void)
{
    return currentFault;
}

/*=========================================================
 * Fault Status
 *=========================================================*/

bool FaultManager_IsFaultActive(void)
{
    return faultActive;
}

/*=========================================================
 * Update
 *=========================================================*/

void FaultManager_Update(void)
{
    if(faultActive)
    {
        StateMachine_SetState(
                STATE_FAULT);
    }
}
