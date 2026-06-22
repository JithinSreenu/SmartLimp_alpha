#ifndef CRC16_H
#define CRC16_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*=========================================================
 * CRC16-CCITT Configuration
 * Polynomial : 0x1021
 * Initial    : 0xFFFF
 *========================================================*/

/**
 * @brief Calculate CRC16-CCITT
 *
 * @param data Pointer to data buffer
 * @param length Number of bytes
 *
 * @return Calculated CRC16
 */
uint16_t CRC16_CCITT(const uint8_t *data,
                     uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* CRC16_H */
