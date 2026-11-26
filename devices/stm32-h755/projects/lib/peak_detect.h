/* peak_detect.h — thresholded peak detector for the heartbeat PPG project.
 * State machine: below threshold -> rising above -> peak when falling.
 * Refractory period prevents double-counting one heartbeat's ringing. */
#ifndef PEAK_DETECT_H
#define PEAK_DETECT_H
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int32_t threshold;
    uint32_t refractory_ticks;
    uint32_t since_last;
    uint32_t count;
    bool armed;
} peak_detect_t;

void peak_detect_init(peak_detect_t *pd, int32_t threshold, uint32_t refractory_ticks);
/* feed one sample per tick; returns true on the tick a beat is counted */
bool peak_detect_step(peak_detect_t *pd, int32_t sample);

#endif
