#ifndef ADC_MANAGER_H
#define ADC_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "adc.h"
#include "shared_types.h"

/*=========================================================
 * ADC Channel Mapping
 *========================================================*/
typedef enum
{
    ADC_CHANNEL_LOADCELL = 0,

    ADC_CHANNEL_SPOOL,

    ADC_CHANNEL_KNEE,

    ADC_CHANNEL_BATTERY,

    ADC_CHANNEL_COUNT

}ADCChannel_t;

/*=========================================================
 * Public Functions
 *========================================================*/

/**
 * @brief Initialize ADC manager
 */
void ADC_Manager_Init(void);

/**
 * @brief Start ADC DMA
 */
void ADC_Manager_Start(void);

/**
 * @brief Stop ADC DMA
 */
void ADC_Manager_Stop(void);

/**
 * @brief Update internal ADC data
 */
void ADC_Manager_Update(void);

/**
 * @brief Get complete ADC data
 */
ADCData_t ADC_Manager_GetData(void);

/**
 * @brief Get Load Cell ADC
 */
uint16_t ADC_GetLoadCellRaw(void);

/**
 * @brief Get Spool Hall ADC
 */
uint16_t ADC_GetSpoolRaw(void);

/**
 * @brief Get Knee Hall ADC
 */
uint16_t ADC_GetKneeRaw(void);

/**
 * @brief Get Battery ADC
 */
uint16_t ADC_GetBatteryRaw(void);

/**
 * @brief ADC health status
 */
bool ADC_IsHealthy(void);

/**
 * @brief DMA complete callback
 */
void ADC_DMA_ConvCpltCallback(void);

#ifdef __cplusplus
}
#endif

#endif
