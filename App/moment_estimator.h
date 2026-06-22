#ifndef MOMENT_ESTIMATOR_H
#define MOMENT_ESTIMATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void MomentEstimator_Init(void);

void MomentEstimator_Update(int16_t force);

int16_t MomentEstimator_GetMoment(void);

#ifdef __cplusplus
}
#endif

#endif
