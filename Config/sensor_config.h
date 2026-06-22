#ifndef SENSOR_CONFIG_H
#define SENSOR_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
 * Load Cell Configuration
 *========================================================*/

/*
 * Raw ADC Range
 * STM32U585 ADC Resolution = 16-bit
 */
#define LOADCELL_ADC_MIN_RAW            (0U)
#define LOADCELL_ADC_MAX_RAW            (65535U)

/*
 * Engineering Force Range
 * Units: kgf or normalized force units
 */
#define FORCE_MIN_VALUE                 (-200)
#define FORCE_MAX_VALUE                 (200)

/*
 * Calibration Values
 * To be determined during system calibration
 */
#define LOADCELL_ZERO_OFFSET            (32768)
#define LOADCELL_SCALE_FACTOR           (1000.0f)

/*=========================================================
 * Spool Hall Sensor
 *========================================================*/

#define SPOOL_ANGLE_MIN                 (0U)
#define SPOOL_ANGLE_MAX                 (100U)

/*
 * ADC limits after calibration
 */
#define SPOOL_ADC_MIN                   (500U)
#define SPOOL_ADC_MAX                   (65000U)

/*=========================================================
 * Knee Hall Sensor
 *========================================================*/

#define KNEE_ANGLE_MIN                  (-200)
#define KNEE_ANGLE_MAX                  (200)

#define KNEE_ADC_MIN                    (500U)
#define KNEE_ADC_MAX                    (65000U)

/*=========================================================
 * Moment Calculation
 *========================================================*/

/*
 * Moment = Force × Lever Arm
 *
 * Example:
 * Lever Arm = 0.25 m
 *
 * Stored as:
 * moment_x10
 */
#define LEVER_ARM_MM                    (250U)

#define MOMENT_MIN_VALUE                (-3000)
#define MOMENT_MAX_VALUE                (3000)

/*=========================================================
 * Battery Monitoring
 *========================================================*/

/*
 * Single Cell Li-Ion
 *
 * Full     = 4.20V
 * Nominal  = 3.70V
 * Critical = 3.30V
 */

#define BATTERY_FULL_MV                 (4200U)

#define BATTERY_NOMINAL_MV              (3700U)

#define BATTERY_LOW_MV                  (3400U)

#define BATTERY_CRITICAL_MV             (3300U)

#define BATTERY_MAX_MV                  (4200U)

#define BATTERY_MIN_MV                  (3000U)

/*=========================================================
 * ADC Fault Detection
 *========================================================*/

#define ADC_STUCK_THRESHOLD             (10U)

#define ADC_FAULT_COUNT_LIMIT           (100U)

/*=========================================================
 * Filtering Parameters
 *========================================================*/

/*
 * Moving Average
 */
#define MOVING_AVERAGE_WINDOW_SIZE      (16U)

/*
 * IIR Filter Alpha
 *
 * y = alpha*x + (1-alpha)*y
 */
#define IIR_ALPHA                       (0.15f)

/*=========================================================
 * Standing Detection
 *========================================================*/

#define STANDING_FORCE_THRESHOLD        (50)

/*=========================================================
 * Walking Detection
 *========================================================*/

#define WALKING_FORCE_THRESHOLD         (20)

/*=========================================================
 * Sitting Detection
 *========================================================*/

#define SITTING_KNEE_ANGLE_THRESHOLD    (90)

/*=========================================================
 * Sensor Timeout
 *========================================================*/

#define SENSOR_TIMEOUT_MS               (500U)

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_CONFIG_H */
