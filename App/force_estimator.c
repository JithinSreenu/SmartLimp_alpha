#include "force_estimator.h"

#include "sensor_config.h"

/*=========================================================
 * Private Variables
 *========================================================*/

static int16_t estimatedForce = 0;

/*
 * Example calibration points
 *
 * MUST be replaced during real calibration
 */
#define FORCE_ADC_MIN      5000U
#define FORCE_ADC_MAX      60000U

/*=========================================================
 * Initialize
 *========================================================*/
void ForceEstimator_Init(void)
{
    estimatedForce = 0;
}

/*=========================================================
 * Update
 *========================================================*/
void ForceEstimator_Update(uint16_t filteredADC)
{
    float normalized;

    if(filteredADC < FORCE_ADC_MIN)
    {
        filteredADC = FORCE_ADC_MIN;
    }

    if(filteredADC > FORCE_ADC_MAX)
    {
        filteredADC = FORCE_ADC_MAX;
    }

    normalized =
        (float)(filteredADC - FORCE_ADC_MIN) /
        (float)(FORCE_ADC_MAX - FORCE_ADC_MIN);

    estimatedForce =
        (int16_t)
        (
            FORCE_MIN_VALUE +
            (normalized *
            (FORCE_MAX_VALUE - FORCE_MIN_VALUE))
        );
}

/*=========================================================
 * Get Force
 *========================================================*/
int16_t ForceEstimator_GetForce(void)
{
    return estimatedForce;
}
