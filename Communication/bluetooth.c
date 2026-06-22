#include "bluetooth.h"

#include <string.h>

#include "packet_protocol.h"
#include "uart_dma.h"

/*=========================================================
 * Private Variables
 *=========================================================*/

static uint8_t txPacket[64];

static uint8_t rxPacket[64];

static CommandID_t lastCommand =
        CMD_NOP;

static bool bluetoothConnected =
        false;

/*=========================================================
 * Initialize
 *=========================================================*/

void Bluetooth_Init(void)
{
    UART_DMA_Init();

    UART_DMA_StartReception();

    lastCommand = CMD_NOP;

    bluetoothConnected = false;
}

/*=========================================================
 * Periodic Update
 *=========================================================*/

void Bluetooth_Update(void)
{
    Bluetooth_ProcessRx();
}

/*=========================================================
 * Send Telemetry
 *=========================================================*/

bool Bluetooth_SendTelemetry(
        const Telemetry_t *telemetry)
{
    uint16_t packetLength;

    if(telemetry == NULL)
    {
        return false;
    }

    if(!Packet_BuildTelemetry(
            telemetry,
            txPacket,
            &packetLength))
    {
        return false;
    }

    return UART_DMA_Transmit(
            txPacket,
            packetLength);
}

/*=========================================================
 * Process Incoming Packets
 *=========================================================*/

void Bluetooth_ProcessRx(void)
{
    uint16_t rxLength;

    Packet_t packet;

    rxLength =
        UART_DMA_GetRxData(
            rxPacket,
            sizeof(rxPacket));

    if(rxLength == 0)
    {
        return;
    }

    if(!Packet_Parse(
            rxPacket,
            rxLength,
            &packet))
    {
        return;
    }

    bluetoothConnected = true;

    if(packet.packetType != PKT_COMMAND)
    {
        return;
    }

    if(packet.payloadLength < 1)
    {
        return;
    }

    lastCommand =
        (CommandID_t)packet.payload[0];
}

/*=========================================================
 * Connection Status
 *=========================================================*/

bool Bluetooth_IsConnected(void)
{
    return bluetoothConnected;
}

/*=========================================================
 * Last Command
 *=========================================================*/

CommandID_t Bluetooth_GetLastCommand(void)
{
    CommandID_t cmd;

    cmd = lastCommand;

    lastCommand = CMD_NOP;

    return cmd;
}
