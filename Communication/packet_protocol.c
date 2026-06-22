#include "packet_protocol.h"

#include <string.h>

#include "protocol_config.h"
#include "crc16.h"

bool Packet_BuildTelemetry(
        const Telemetry_t *telemetry,
        uint8_t *buffer,
        uint16_t *length)
{
    uint16_t index = 0;

    uint16_t crc;

    if((telemetry == NULL) ||
       (buffer == NULL) ||
       (length == NULL))
    {
        return false;
    }

    buffer[index++] = PACKET_START_BYTE;

    buffer[index++] = PKT_TELEMETRY;

    buffer[index++] = PROTOCOL_VERSION;

    buffer[index++] = TELEMETRY_PAYLOAD_SIZE;

    buffer[index++] = telemetry->spoolAngle;

    memcpy(&buffer[index],
           &telemetry->force,
           sizeof(int16_t));
    index += sizeof(int16_t);

    memcpy(&buffer[index],
           &telemetry->kneeAngle,
           sizeof(int16_t));
    index += sizeof(int16_t);

    memcpy(&buffer[index],
           &telemetry->moment,
           sizeof(int16_t));
    index += sizeof(int16_t);

    buffer[index++] = telemetry->stateID;

    memcpy(&buffer[index],
           &telemetry->battery_mV,
           sizeof(uint16_t));
    index += sizeof(uint16_t);

    crc =
        CRC16_CCITT(
            &buffer[1],
            index - 1);

    buffer[index++] =
            (uint8_t)(crc & 0xFF);

    buffer[index++] =
            (uint8_t)(crc >> 8);

    buffer[index++] =
            PACKET_STOP_BYTE;

    *length = index;

    return true;
}

bool Packet_Parse(
        const uint8_t *buffer,
        uint16_t length,
        Packet_t *packet)
{
    uint16_t calculatedCRC;

    uint16_t receivedCRC;

    if(length < 7)
    {
        return false;
    }

    if(buffer[0] != PACKET_START_BYTE)
    {
        return false;
    }

    if(buffer[length - 1] != PACKET_STOP_BYTE)
    {
        return false;
    }

    receivedCRC =
        (uint16_t)buffer[length - 3] |
        ((uint16_t)buffer[length - 2] << 8);

    calculatedCRC =
        CRC16_CCITT(
            &buffer[1],
            length - 4);

    if(receivedCRC != calculatedCRC)
    {
        return false;
    }

    packet->startByte = buffer[0];
    packet->packetType = buffer[1];
    packet->version = buffer[2];
    packet->payloadLength = buffer[3];

    memcpy(packet->payload,
           &buffer[4],
           packet->payloadLength);

    packet->crc = receivedCRC;

    packet->stopByte =
            buffer[length - 1];

    return true;
}
