#include "moment_estimator.h"

#include "sensor_config.h"

/*=========================================================
 * Private Variables
 *========================================================*/

static int16_t estimatedMoment = 0;

/*=========================================================
 * Initialize
 *========================================================*/
void MomentEstimator_Init(void)
{
    estimatedMoment = 0;
}

/*=========================================================
 * Update
 *========================================================*/
void MomentEstimator_Update(int16_t force)
{
    int32_t moment;

    /*
     * Moment = Force × Lever Arm
     *
     * Lever arm in mm
     */

    moment =
        (int32_t)force *
        (int32_t)LEVER_ARM_MM;

    /*
     * Scale down
     */

    moment /= 10;

    if(moment > MOMENT_MAX_VALUE)
    {
        moment = MOMENT_MAX_VALUE;
    }

    if(moment < MOMENT_MIN_VALUE)
    {
        moment = MOMENT_MIN_VALUE;
    }

    estimatedMoment = (int16_t)moment;
}

/*=========================================================
 * Get Moment
 *========================================================*/
int16_t MomentEstimator_GetMoment(void)
{
    return estimatedMoment;
}
