#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*=========================================================
 * Configuration
 *========================================================*/
#define MA_MAX_WINDOW_SIZE     (32U)

/*=========================================================
 * Moving Average Object
 *========================================================*/
typedef struct
{
    uint16_t buffer[MA_MAX_WINDOW_SIZE];

    uint32_t sum;

    uint16_t index;

    uint16_t count;

    uint16_t windowSize;

} MovingAverage_t;

/*=========================================================
 * Public Functions
 *========================================================*/

/**
 * @brief Initialize Moving Average Filter
 *
 * @param filter Pointer to filter object
 * @param windowSize Number of samples
 */
void MA_Init(MovingAverage_t *filter,
             uint16_t windowSize);

/**
 * @brief Reset filter
 *
 * @param filter Pointer to filter object
 */
void MA_Reset(MovingAverage_t *filter);

/**
 * @brief Add new sample
 *
 * @param filter Pointer to filter object
 * @param sample New sample
 */
void MA_AddSample(MovingAverage_t *filter,
                  uint16_t sample);

/**
 * @brief Get filtered value
 *
 * @param filter Pointer to filter object
 *
 * @return Filtered value
 */
uint16_t MA_GetValue(MovingAverage_t *filter);

#ifdef __cplusplus
}
#endif

#endif /* MOVING_AVERAGE_H */
