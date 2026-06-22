#include "hall_sensor.h"

#include "sensor_config.h"

/*=========================================================
 * Calibration Data
 *=========================================================*/

static uint16_t spoolADC_Min;
static uint16_t spoolADC_Max;

static uint16_t kneeADC_Min;
static uint16_t kneeADC_Max;

/*=========================================================
 * Sensor Values
 *=========================================================*/

static HallSensorData_t hallData;

/*=========================================================
 * Private Functions
 *=========================================================*/

static uint8_t ConvertSpoolAngle(
        uint16_t adcValue);

static int16_t ConvertKneeAngle(
        uint16_t adcValue);

/*=========================================================
 * Initialize
 *=========================================================*/

void HallSensor_Init(void)
{
    spoolADC_Min = SPOOL_ADC_MIN;
    spoolADC_Max = SPOOL_ADC_MAX;

    kneeADC_Min = KNEE_ADC_MIN;
    kneeADC_Max = KNEE_ADC_MAX;

    hallData.spoolAnglePercent = 0;
    hallData.kneeAngleDeg = 0;
}

/*=========================================================
 * Update
 *=========================================================*/

void HallSensor_Update(
        uint16_t spoolADC,
        uint16_t kneeADC)
{
    hallData.spoolAnglePercent =
            ConvertSpoolAngle(spoolADC);

    hallData.kneeAngleDeg =
            ConvertKneeAngle(kneeADC);
}

/*=========================================================
 * Spool Conversion
 *=========================================================*/

static uint8_t ConvertSpoolAngle(
        uint16_t adcValue)
{
    uint32_t value;

    if(adcValue < spoolADC_Min)
    {
        adcValue = spoolADC_Min;
    }

    if(adcValue > spoolADC_Max)
    {
        adcValue = spoolADC_Max;
    }

    value =
        ((uint32_t)(adcValue - spoolADC_Min)
         * 100U) /
        (spoolADC_Max - spoolADC_Min);

    return (uint8_t)value;
}

/*=========================================================
 * Knee Conversion
 *=========================================================*/

static int16_t ConvertKneeAngle(
        uint16_t adcValue)
{
    int32_t angle;

    if(adcValue < kneeADC_Min)
    {
        adcValue = kneeADC_Min;
    }

    if(adcValue > kneeADC_Max)
    {
        adcValue = kneeADC_Max;
    }

    angle =
        ((int32_t)(adcValue - kneeADC_Min)
         * 400) /
        (kneeADC_Max - kneeADC_Min);

    angle -= 200;

    return (int16_t)angle;
}

/*=========================================================
 * Get Spool Angle
 *=========================================================*/

uint8_t HallSensor_GetSpoolAngle(void)
{
    return hallData.spoolAnglePercent;
}

/*=========================================================
 * Get Knee Angle
 *=========================================================*/

int16_t HallSensor_GetKneeAngle(void)
{
    return hallData.kneeAngleDeg;
}

/*=========================================================
 * Get Data
 *=========================================================*/

HallSensorData_t HallSensor_GetData(void)
{
    return hallData;
}

/*=========================================================
 * Calibration Update
 *=========================================================*/

void HallSensor_SetCalibration(
        uint16_t spoolMin,
        uint16_t spoolMax,
        uint16_t kneeMin,
        uint16_t kneeMax)
{
    spoolADC_Min = spoolMin;
    spoolADC_Max = spoolMax;

    kneeADC_Min = kneeMin;
    kneeADC_Max = kneeMax;
}
