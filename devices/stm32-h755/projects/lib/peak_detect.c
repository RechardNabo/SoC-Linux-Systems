#include "peak_detect.h"

void peak_detect_init(peak_detect_t *pd, int32_t threshold, uint32_t refractory_ticks)
{
    pd->threshold = threshold;
    pd->refractory_ticks = refractory_ticks;
    pd->since_last = refractory_ticks;   /* ready immediately */
    pd->count = 0U;
    pd->armed = false;
}

bool peak_detect_step(peak_detect_t *pd, int32_t sample)
{
    bool counted = false;
    if (pd->since_last < 0xFFFFFFFFUL) pd->since_last++;
    if (sample >= pd->threshold) {
        pd->armed = true;
    } else if (pd->armed && pd->since_last >= pd->refractory_ticks) {
        /* fell back below threshold after a peak, refractory elapsed */
        pd->count++;
        pd->since_last = 0U;
        pd->armed = false;
        counted = true;
    } else if (pd->armed) {
        pd->armed = false;   /* fell back during refractory: noise, not a beat */
    }
    return counted;
}
