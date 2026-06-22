#include "moving_average.h"

#include <string.h>

/*=========================================================
 * Initialize
 *========================================================*/
void MA_Init(MovingAverage_t *filter,
             uint16_t windowSize)
{
    if(filter == NULL)
    {
        return;
    }

    if(windowSize > MA_MAX_WINDOW_SIZE)
    {
        windowSize = MA_MAX_WINDOW_SIZE;
    }

    memset(filter->buffer,
           0,
           sizeof(filter->buffer));

    filter->sum = 0;

    filter->index = 0;

    filter->count = 0;

    filter->windowSize = windowSize;
}

/*=========================================================
 * Reset
 *========================================================*/
void MA_Reset(MovingAverage_t *filter)
{
    if(filter == NULL)
    {
        return;
    }

    memset(filter->buffer,
           0,
           sizeof(filter->buffer));

    filter->sum = 0;

    filter->index = 0;

    filter->count = 0;
}

/*=========================================================
 * Add Sample
 *========================================================*/
void MA_AddSample(MovingAverage_t *filter,
                  uint16_t sample)
{
    if(filter == NULL)
    {
        return;
    }

    filter->sum -= filter->buffer[filter->index];

    filter->buffer[filter->index] = sample;

    filter->sum += sample;

    filter->index++;

    if(filter->index >= filter->windowSize)
    {
        filter->index = 0;
    }

    if(filter->count < filter->windowSize)
    {
        filter->count++;
    }
}

/*=========================================================
 * Get Average
 *========================================================*/
uint16_t MA_GetValue(MovingAverage_t *filter)
{
    if(filter == NULL)
    {
        return 0;
    }

    if(filter->count == 0)
    {
        return 0;
    }

    return (uint16_t)(filter->sum / filter->count);
}
