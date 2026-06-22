#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*=========================================================
 * Hall Sensor Data
 *=========================================================*/
typedef struct
{
    uint8_t spoolAnglePercent;

    int16_t kneeAngleDeg;

} HallSensorData_t;

/*=========================================================
 * Public Functions
 *=========================================================*/

void HallSensor_Init(void);

void HallSensor_Update(
        uint16_t spoolADC,
        uint16_t kneeADC);

uint8_t HallSensor_GetSpoolAngle(void);

int16_t HallSensor_GetKneeAngle(void);

HallSensorData_t HallSensor_GetData(void);

void HallSensor_SetCalibration(
        uint16_t spoolMin,
        uint16_t spoolMax,
        uint16_t kneeMin,
        uint16_t kneeMax);

#ifdef __cplusplus
}
#endif

#endif
