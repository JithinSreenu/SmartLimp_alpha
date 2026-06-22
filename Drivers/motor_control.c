#include "motor_control.h"

#include "tim.h"
#include "gpio.h"
#include "project_config.h"

static MotorState_t motorState;

static bool motorHealthy;

static uint32_t motorRunTime;

/*=========================================================
 * Private Functions
 *=========================================================*/

static void SetPWM_TIM1(uint16_t duty);
static void SetPWM_TIM2(uint16_t duty);

/*=========================================================
 * Initialize
 *=========================================================*/

void MotorControl_Init(void)
{
    motorState = MOTOR_STOPPED;

    motorHealthy = true;

    motorRunTime = 0;

    HAL_TIM_PWM_Start(
            &htim1,
            TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(
            &htim2,
            TIM_CHANNEL_1);

    MotorControl_Stop();
}

/*=========================================================
 * Update
 *=========================================================*/

void MotorControl_Update(
        const GaitCommand_t *command)
{
    if(command == NULL)
    {
        return;
    }

    if(command->motorOpenCmd)
    {
        MotorControl_OpenValve(
                command->pwmDuty);

        return;
    }

    if(command->motorCloseCmd)
    {
        MotorControl_CloseValve(
                command->pwmDuty);

        return;
    }

    MotorControl_Stop();
}

/*=========================================================
 * Open Valve
 *=========================================================*/

void MotorControl_OpenValve(
        uint16_t pwmDuty)
{
    if(pwmDuty > PWM_MAX_DUTY)
    {
        pwmDuty = PWM_MAX_DUTY;
    }

    HAL_GPIO_WritePin(
            GPIOA,
            GPIO_PIN_0,
            GPIO_SET);

    HAL_GPIO_WritePin(
            GPIOA,
            GPIO_PIN_1,
            GPIO_RESET);

    SetPWM_TIM1(pwmDuty);

    SetPWM_TIM2(0);

    motorState = MOTOR_OPENING;
}

/*=========================================================
 * Close Valve
 *=========================================================*/

void MotorControl_CloseValve(
        uint16_t pwmDuty)
{
    if(pwmDuty > PWM_MAX_DUTY)
    {
        pwmDuty = PWM_MAX_DUTY;
    }

    HAL_GPIO_WritePin(
            GPIOA,
            GPIO_PIN_0,
            GPIO_RESET);

    HAL_GPIO_WritePin(
            GPIOA,
            GPIO_PIN_1,
            GPIO_SET);

    SetPWM_TIM1(0);

    SetPWM_TIM2(pwmDuty);

    motorState = MOTOR_CLOSING;
}

/*=========================================================
 * Stop
 *=========================================================*/

void MotorControl_Stop(void)
{
    SetPWM_TIM1(0);

    SetPWM_TIM2(0);

    HAL_GPIO_WritePin(
            GPIOA,
            GPIO_PIN_0,
            GPIO_RESET);

    HAL_GPIO_WritePin(
            GPIOA,
            GPIO_PIN_1,
            GPIO_RESET);

    motorState = MOTOR_STOPPED;
}

/*=========================================================
 * PWM Helpers
 *=========================================================*/

static void SetPWM_TIM1(
        uint16_t duty)
{
    __HAL_TIM_SET_COMPARE(
            &htim1,
            TIM_CHANNEL_1,
            duty);
}

static void SetPWM_TIM2(
        uint16_t duty)
{
    __HAL_TIM_SET_COMPARE(
            &htim2,
            TIM_CHANNEL_1,
            duty);
}

/*=========================================================
 * Status
 *=========================================================*/

MotorState_t MotorControl_GetState(void)
{
    return motorState;
}

bool MotorControl_IsHealthy(void)
{
    return motorHealthy;
}
