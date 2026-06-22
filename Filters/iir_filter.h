#ifndef IIR_FILTER_H
#define IIR_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*=========================================================
 * First Order IIR Filter
 *
 * y = alpha*x + (1-alpha)*y_prev
 *
 *=========================================================*/

typedef struct
{
    float alpha;

    float output;

    uint8_t initialized;

} IIRFilter_t;

/*=========================================================
 * Public Functions
 *=========================================================*/

/**
 * @brief Initialize IIR filter
 *
 * @param filter Filter object
 * @param alpha Filter coefficient
 */
void IIR_Init(IIRFilter_t *filter,
              float alpha);

/**
 * @brief Reset filter
 *
 * @param filter Filter object
 */
void IIR_Reset(IIRFilter_t *filter);

/**
 * @brief Update filter
 *
 * @param filter Filter object
 * @param input New sample
 *
 * @return Filtered output
 */
float IIR_Update(IIRFilter_t *filter,
                 float input);

/**
 * @brief Get current output
 *
 * @param filter Filter object
 *
 * @return Current output
 */
float IIR_GetValue(IIRFilter_t *filter);

#ifdef __cplusplus
}
#endif

#endif /* IIR_FILTER_H */
