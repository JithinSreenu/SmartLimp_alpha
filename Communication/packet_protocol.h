#ifndef PACKET_PROTOCOL_H
#define PACKET_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "shared_types.h"

#define PACKET_MAX_PAYLOAD_SIZE     32U

typedef struct
{
    uint8_t startByte;

    uint8_t packetType;

    uint8_t version;

    uint8_t payloadLength;

    uint8_t payload[PACKET_MAX_PAYLOAD_SIZE];

    uint16_t crc;

    uint8_t stopByte;

} Packet_t;

bool Packet_BuildTelemetry(
        const Telemetry_t *telemetry,
        uint8_t *buffer,
        uint16_t *length);

bool Packet_Parse(
        const uint8_t *buffer,
        uint16_t length,
        Packet_t *packet);

#ifdef __cplusplus
}
#endif

#endif
