#include "FreeRTOS.h"
#include "task.h"

#include "task_adc.h"
#include "task_control.h"
#include "task_motor.h"
#include "task_bluetooth.h"
#include "task_safety.h"
#include "task_watchdog.h"

/*=========================================================
 * Task Handles
 *=========================================================*/

TaskHandle_t adcTaskHandle;
TaskHandle_t controlTaskHandle;
TaskHandle_t motorTaskHandle;
TaskHandle_t bluetoothTaskHandle;
TaskHandle_t safetyTaskHandle;
TaskHandle_t watchdogTaskHandle;

/*=========================================================
 * ADC Task
 *=========================================================*/

static void ADC_Task(void *argument)
{
    TickType_t lastWakeTime;

    lastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        Task_ADC_Run();

        vTaskDelayUntil(
            &lastWakeTime,
            pdMS_TO_TICKS(5));
    }
}

/*=========================================================
 * Control Task
 *=========================================================*/

static void Control_Task(void *argument)
{
    TickType_t lastWakeTime;

    lastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        Task_Control_Run();

        vTaskDelayUntil(
            &lastWakeTime,
            pdMS_TO_TICKS(5));
    }
}

/*=========================================================
 * Motor Task
 *=========================================================*/

static void Motor_Task(void *argument)
{
    TickType_t lastWakeTime;

    lastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        Task_Motor_Run();

        vTaskDelayUntil(
            &lastWakeTime,
            pdMS_TO_TICKS(1));
    }
}

/*=========================================================
 * Bluetooth Task
 *=========================================================*/

static void Bluetooth_Task(void *argument)
{
    TickType_t lastWakeTime;

    lastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        Task_Bluetooth_Run();

        vTaskDelayUntil(
            &lastWakeTime,
            pdMS_TO_TICKS(50));
    }
}

/*=========================================================
 * Safety Task
 *=========================================================*/

static void Safety_Task(void *argument)
{
    TickType_t lastWakeTime;

    lastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        Task_Safety_Run();

        vTaskDelayUntil(
            &lastWakeTime,
            pdMS_TO_TICKS(1));
    }
}

/*=========================================================
 * Watchdog Task
 *=========================================================*/

static void Watchdog_Task(void *argument)
{
    TickType_t lastWakeTime;

    lastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        Task_Watchdog_Run();

        vTaskDelayUntil(
            &lastWakeTime,
            pdMS_TO_TICKS(100));
    }
}

/*=========================================================
 * Create Tasks
 *=========================================================*/

void MX_FREERTOS_Init(void)
{
    xTaskCreate(
        ADC_Task,
        "ADC",
        512,
        NULL,
        3,
        &adcTaskHandle);

    xTaskCreate(
        Control_Task,
        "CTRL",
        1024,
        NULL,
        3,
        &controlTaskHandle);

    xTaskCreate(
        Motor_Task,
        "MOTOR",
        512,
        NULL,
        4,
        &motorTaskHandle);

    xTaskCreate(
        Bluetooth_Task,
        "BT",
        1024,
        NULL,
        2,
        &bluetoothTaskHandle);

    xTaskCreate(
        Safety_Task,
        "SAFE",
        512,
        NULL,
        5,
        &safetyTaskHandle);

    xTaskCreate(
        Watchdog_Task,
        "WDG",
        512,
        NULL,
        1,
        &watchdogTaskHandle);
}
