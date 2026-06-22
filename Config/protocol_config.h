#ifndef PROTOCOL_CONFIG_H
#define PROTOCOL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
 * Protocol Version
 *========================================================*/
#define PROTOCOL_VERSION               (0x01U)

/*=========================================================
 * Packet Delimiters
 *========================================================*/
#define PACKET_START_BYTE              (0xAAU)
#define PACKET_STOP_BYTE               (0x55U)

/*=========================================================
 * Packet Sizes
 *========================================================*/
#define PACKET_HEADER_SIZE             (4U)

#define PACKET_CRC_SIZE                (2U)

#define PACKET_FOOTER_SIZE             (1U)

#define MAX_PAYLOAD_SIZE               (32U)

#define MAX_PACKET_SIZE                (64U)

/*=========================================================
 * Communication Timeouts
 *========================================================*/
#define RX_TIMEOUT_MS                  (1000U)

#define TX_TIMEOUT_MS                  (1000U)

/*=========================================================
 * Packet IDs
 *========================================================*/
typedef enum
{
    PKT_TELEMETRY      = 0x01,

    PKT_COMMAND        = 0x02,

    PKT_DIAGNOSTIC     = 0x03,

    PKT_CALIBRATION    = 0x04,

    PKT_FAULT          = 0x05,

    PKT_ACK            = 0x06,

    PKT_NACK           = 0x07

}PacketID_t;

/*=========================================================
 * System States
 *========================================================*/
typedef enum
{
    STATE_IDLE = 0,

    STATE_STANDING,

    STATE_WALKING,

    STATE_SITTING,

    STATE_STAIR_ASCENT,

    STATE_STAIR_DESCENT,

    STATE_CALIBRATION,

    STATE_FAULT

}SystemState_t;

/*=========================================================
 * Command IDs
 *========================================================*/
typedef enum
{
    CMD_NOP                    = 0x00,

    CMD_START                  = 0x01,

    CMD_STOP                   = 0x02,

    CMD_CALIBRATE              = 0x03,

    CMD_REQUEST_STATUS         = 0x04,

    CMD_REQUEST_DIAGNOSTIC     = 0x05,

    CMD_RESET_FAULT            = 0x06

}CommandID_t;

/*=========================================================
 * Fault Codes
 *========================================================*/
typedef enum
{
    FAULT_NONE = 0,

    FAULT_ADC,

    FAULT_LOADCELL,

    FAULT_HALL_SENSOR,

    FAULT_BATTERY_LOW,

    FAULT_BATTERY_CRITICAL,

    FAULT_MOTOR_TIMEOUT,

    FAULT_COMMUNICATION,

    FAULT_WATCHDOG

}FaultCode_t;

/*=========================================================
 * Telemetry Payload Size
 *========================================================*/
#define TELEMETRY_PAYLOAD_SIZE         (10U)

#ifdef __cplusplus
}
#endif

#endif
