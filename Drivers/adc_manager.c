#include "adc_manager.h"

#include <string.h>

/*=========================================================
 * Private Variables
 *========================================================*/

/*
 * DMA Buffer
 *
 * Index Mapping
 *
 * [0] Load Cell
 * [1] Spool Hall
 * [2] Knee Hall
 * [3] Battery
 */
static uint16_t adcRawBuffer[ADC_CHANNEL_COUNT];

/*
 * Structured ADC Data
 */
static ADCData_t adcData;

/*
 * Health Monitoring
 */
static bool adcHealthy = true;

/*
 * Previous Samples
 */
static uint16_t previousBuffer[ADC_CHANNEL_COUNT];

/*
 * Stuck Counter
 */
static uint32_t stuckCounter = 0;

/*=========================================================
 * Initialization
 *========================================================*/
void ADC_Manager_Init(void)
{
    memset(adcRawBuffer, 0, sizeof(adcRawBuffer));

    memset(&adcData, 0, sizeof(adcData));

    memset(previousBuffer, 0, sizeof(previousBuffer));

    adcHealthy = true;

    stuckCounter = 0;
}

/*=========================================================
 * Start DMA
 *========================================================*/
void ADC_Manager_Start(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1,
                                ADC_CALIB_OFFSET,
                                ADC_SINGLE_ENDED);

    HAL_ADC_Start_DMA(&hadc1,
                      (uint32_t*)adcRawBuffer,
                      ADC_CHANNEL_COUNT);
}

/*=========================================================
 * Stop DMA
 *========================================================*/
void ADC_Manager_Stop(void)
{
    HAL_ADC_Stop_DMA(&hadc1);
}

/*=========================================================
 * Update ADC Data
 *========================================================*/
void ADC_Manager_Update(void)
{
    adcData.loadCellADC = adcRawBuffer[0];

    adcData.spoolADC = adcRawBuffer[1];

    adcData.kneeADC = adcRawBuffer[2];

    adcData.batteryADC = adcRawBuffer[3];

    /*
     * Simple Health Check
     */

    if((adcRawBuffer[0] == previousBuffer[0]) &&
       (adcRawBuffer[1] == previousBuffer[1]) &&
       (adcRawBuffer[2] == previousBuffer[2]) &&
       (adcRawBuffer[3] == previousBuffer[3]))
    {
        stuckCounter++;
    }
    else
    {
        stuckCounter = 0;
    }

    memcpy(previousBuffer,
           adcRawBuffer,
           sizeof(adcRawBuffer));

    if(stuckCounter > 1000)
    {
        adcHealthy = false;
    }
}

/*=========================================================
 * Get ADC Data
 *========================================================*/
ADCData_t ADC_Manager_GetData(void)
{
    return adcData;
}

/*=========================================================
 * Raw Channel Access
 *========================================================*/
uint16_t ADC_GetLoadCellRaw(void)
{
    return adcRawBuffer[0];
}

uint16_t ADC_GetSpoolRaw(void)
{
    return adcRawBuffer[1];
}

uint16_t ADC_GetKneeRaw(void)
{
    return adcRawBuffer[2];
}

uint16_t ADC_GetBatteryRaw(void)
{
    return adcRawBuffer[3];
}

/*=========================================================
 * Health Status
 *========================================================*/
bool ADC_IsHealthy(void)
{
    return adcHealthy;
}

/*=========================================================
 * DMA Complete Callback
 *========================================================*/
void ADC_DMA_ConvCpltCallback(void)
{
    ADC_Manager_Update();
}
