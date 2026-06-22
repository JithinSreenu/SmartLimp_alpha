#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*=========================================================
 * Sensor Data Structure
 *=========================================================
 *
 * Updated by:
 * ADC Task
 *
 * Read by:
 * Force Estimator
 * Moment Estimator
 * State Machine
 * Telemetry
 *
 *=========================================================*/
typedef struct
{
    int16_t force;

    int16_t kneeAngle;

    uint8_t spoolAngle;

    int16_t moment;

    uint16_t battery_mV;

} SensorData_t;

/*=========================================================
 * Telemetry Structure
 *=========================================================*/
typedef struct
{
    uint8_t spoolAngle;

    int16_t force;

    int16_t kneeAngle;

    int16_t moment;

    uint8_t stateID;

    uint16_t battery_mV;

} Telemetry_t;

/*=========================================================
 * Command Structure
 *=========================================================*/
typedef struct
{
    uint8_t commandID;

    uint8_t payloadLength;

    uint8_t payload[32];

} CommandPacket_t;

/*=========================================================
 * Fault Structure
 *=========================================================*/
typedef struct
{
    uint8_t faultCode;

    uint32_t timestamp;

} FaultData_t;

/*=========================================================
 * ADC Raw Data
 *=========================================================*/
typedef struct
{
    uint16_t loadCellADC;

    uint16_t spoolADC;

    uint16_t kneeADC;

    uint16_t batteryADC;

} ADCData_t;

/*=========================================================
 * System Status
 *=========================================================*/
typedef struct
{
    bool communicationOK;

    bool batteryOK;

    bool sensorOK;

    bool motorOK;

    bool watchdogOK;

} SystemHealth_t;

#ifdef __cplusplus
}
#endif

#endif
