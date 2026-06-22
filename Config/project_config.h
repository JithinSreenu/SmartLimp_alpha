#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
 * Firmware Information
 *========================================================*/
#define FW_VERSION_MAJOR               (1U)
#define FW_VERSION_MINOR               (0U)
#define FW_VERSION_PATCH               (0U)

/*=========================================================
 * System Timing
 *========================================================*/
#define SYSTEM_TICK_MS                 (1U)

#define ADC_TASK_PERIOD_MS             (5U)

#define CONTROL_TASK_PERIOD_MS         (5U)

#define MOTOR_TASK_PERIOD_MS           (1U)

#define BLUETOOTH_TASK_PERIOD_MS       (50U)

#define SAFETY_TASK_PERIOD_MS          (1U)

#define WATCHDOG_TASK_PERIOD_MS        (100U)

/*=========================================================
 * ADC Configuration
 *========================================================*/
#define ADC_SAMPLE_RATE_HZ             (1000U)

#define ADC_BUFFER_SIZE                (4U)

/*
ADC Channel Assignment

CH0 = Load Cell
CH1 = Spool Hall Sensor
CH2 = Knee Hall Sensor
CH3 = Battery Monitor
*/
#define ADC_CHANNEL_COUNT              (4U)

/*=========================================================
 * UART Configuration
 *========================================================*/
#define UART_BLUETOOTH_BAUDRATE        (115200U)

#define UART_RX_BUFFER_SIZE            (128U)

#define UART_TX_BUFFER_SIZE            (128U)

/*=========================================================
 * Telemetry Configuration
 *========================================================*/
#define TELEMETRY_PERIOD_MS            (50U)

/*=========================================================
 * Queue Sizes
 *========================================================*/
#define SENSOR_QUEUE_LENGTH            (8U)

#define COMMAND_QUEUE_LENGTH           (8U)

/*=========================================================
 * Watchdog
 *========================================================*/
#define WATCHDOG_TIMEOUT_MS            (1000U)

/*=========================================================
 * PWM Configuration
 *========================================================*/
#define PWM_MAX_DUTY                   (1000U)

#define PWM_MIN_DUTY                   (0U)

/*=========================================================
 * Safety
 *========================================================*/
#define MOTOR_TIMEOUT_MS               (500U)

#define COMMUNICATION_TIMEOUT_MS       (1000U)

#ifdef __cplusplus
}
#endif

#endif /* PROJECT_CONFIG_H */
