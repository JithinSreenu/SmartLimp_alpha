#include "iir_filter.h"

/*=========================================================
 * Initialize
 *=========================================================*/
void IIR_Init(IIRFilter_t *filter,
              float alpha)
{
    if(filter == NULL)
    {
        return;
    }

    filter->alpha = alpha;

    filter->output = 0.0f;

    filter->initialized = 0U;
}

/*=========================================================
 * Reset
 *=========================================================*/
void IIR_Reset(IIRFilter_t *filter)
{
    if(filter == NULL)
    {
        return;
    }

    filter->output = 0.0f;

    filter->initialized = 0U;
}

/*=========================================================
 * Update
 *=========================================================*/
float IIR_Update(IIRFilter_t *filter,
                 float input)
{
    if(filter == NULL)
    {
        return 0.0f;
    }

    if(filter->initialized == 0U)
    {
        filter->output = input;

        filter->initialized = 1U;

        return filter->output;
    }

    filter->output =
        (filter->alpha * input) +
        ((1.0f - filter->alpha) * filter->output);

    return filter->output;
}

/*=========================================================
 * Get Value
 *=========================================================*/
float IIR_GetValue(IIRFilter_t *filter)
{
    if(filter == NULL)
    {
        return 0.0f;
    }

    return filter->output;
}
