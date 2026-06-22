#include "battery_monitor.h"

#include "sensor_config.h"
#include "fault_manager.h"

/*=========================================================
 * Configuration
 *=========================================================*/

/*
 * Example:
 *
 * ADC = 0      -> 0mV
 * ADC = 65535  -> 4200mV
 *
 * Replace with actual divider calibration later
 */
#define BATTERY_ADC_MAX      65535U

/*=========================================================
 * Private Variables
 *=========================================================*/

static uint16_t batteryVoltage_mV;

static uint8_t batteryPercentage;

static BatteryStatus_t batteryStatus;

static bool batteryHealthy;

/*=========================================================
 * Private Functions
 *=========================================================*/

static uint16_t ADC_To_mV(uint16_t adc);

static uint8_t Voltage_To_Percentage(
                    uint16_t voltage);

/*=========================================================
 * Initialize
 *=========================================================*/

void BatteryMonitor_Init(void)
{
    batteryVoltage_mV = 0;

    batteryPercentage = 0;

    batteryStatus = BATTERY_STATUS_NORMAL;

    batteryHealthy = true;
}

/*=========================================================
 * Update
 *=========================================================*/

void BatteryMonitor_Update(uint16_t adcValue)
{
    batteryVoltage_mV =
        ADC_To_mV(adcValue);

    batteryPercentage =
        Voltage_To_Percentage(
            batteryVoltage_mV);

    if(batteryVoltage_mV <=
       BATTERY_CRITICAL_MV)
    {
        batteryStatus =
            BATTERY_STATUS_CRITICAL;

        batteryHealthy = false;

        FaultManager_SetFault(
            FAULT_BATTERY_CRITICAL);

        return;
    }

    if(batteryVoltage_mV <=
       BATTERY_LOW_MV)
    {
        batteryStatus =
            BATTERY_STATUS_LOW;

        return;
    }

    if(batteryVoltage_mV >=
       BATTERY_FULL_MV)
    {
        batteryStatus =
            BATTERY_STATUS_FULL;

        return;
    }

    batteryStatus =
        BATTERY_STATUS_NORMAL;
}

/*=========================================================
 * ADC to Voltage
 *=========================================================*/

static uint16_t ADC_To_mV(uint16_t adc)
{
    uint32_t voltage;

    voltage =
        ((uint32_t)adc *
         BATTERY_FULL_MV) /
         BATTERY_ADC_MAX;

    return (uint16_t)voltage;
}

/*=========================================================
 * Voltage to Percentage
 *=========================================================*/

static uint8_t Voltage_To_Percentage(
                    uint16_t voltage)
{
    uint32_t percentage;

    if(voltage >= BATTERY_FULL_MV)
    {
        return 100U;
    }

    if(voltage <= BATTERY_CRITICAL_MV)
    {
        return 0U;
    }

    percentage =
        ((uint32_t)(voltage -
                    BATTERY_CRITICAL_MV)
         * 100U) /
        (BATTERY_FULL_MV -
         BATTERY_CRITICAL_MV);

    return (uint8_t)percentage;
}

/*=========================================================
 * Get Voltage
 *=========================================================*/

uint16_t BatteryMonitor_GetVoltage_mV(void)
{
    return batteryVoltage_mV;
}

/*=========================================================
 * Get Percentage
 *=========================================================*/

uint8_t BatteryMonitor_GetPercentage(void)
{
    return batteryPercentage;
}

/*=========================================================
 * Get Status
 *=========================================================*/

BatteryStatus_t BatteryMonitor_GetStatus(void)
{
    return batteryStatus;
}

/*=========================================================
 * Health Check
 *=========================================================*/

bool BatteryMonitor_IsHealthy(void)
{
    return batteryHealthy;
}
