#include "hysteresis.h"

void hysteresis_init(hysteresis_t *h, int32_t low, int32_t high)
{
    h->low = low;
    h->high = high;
    h->active = false;
}

bool hysteresis_step(hysteresis_t *h, int32_t value)
{
    const bool was = h->active;
    if (value >= h->high) h->active = true;
    else if (value < h->low) h->active = false;
    return h->active && !was;
}

bool hysteresis_state(const hysteresis_t *h)
{
    return h != NULL && h->active;
}
