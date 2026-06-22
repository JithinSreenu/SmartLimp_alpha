#ifndef FORCE_ESTIMATOR_H
#define FORCE_ESTIMATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*=========================================================
 * Force Estimator Interface
 *========================================================*/

/**
 * @brief Initialize force estimator
 */
void ForceEstimator_Init(void);

/**
 * @brief Update force estimation
 *
 * @param filteredADC Filtered ADC value
 */
void ForceEstimator_Update(uint16_t filteredADC);

/**
 * @brief Get estimated force
 *
 * @return Force value
 */
int16_t ForceEstimator_GetForce(void);

#ifdef __cplusplus
}
#endif

#endif
