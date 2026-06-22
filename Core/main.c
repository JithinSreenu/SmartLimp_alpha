#include "main.h"

#include "app_init.h"

#include "freertos.h"

/* Generated Handles */

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart1;

extern TIM_HandleTypeDef htim1;

extern TIM_HandleTypeDef htim2;

extern IWDG_HandleTypeDef hiwdg;

/*=========================================================
 * Function Prototypes
 *=========================================================*/

void SystemClock_Config(void);

/*=========================================================
 * Main
 *=========================================================*/

int main(void)
{
    /* HAL */

    HAL_Init();

    /* Clock */

    SystemClock_Config();

    /* CubeMX Generated */

    MX_GPIO_Init();

    MX_DMA_Init();

    MX_ADC1_Init();

    MX_USART1_UART_Init();

    MX_TIM1_Init();

    MX_TIM2_Init();

    MX_IWDG_Init();

    /* Application */

    App_Init();

    /* RTOS */

    MX_FREERTOS_Init();

    /* Scheduler */

    vTaskStartScheduler();

    while(1)
    {
    }
}
