/* hysteresis.h — threshold event detector for analog projects.
 * Above high = active, below low = inactive, between = keep previous.
 * Without the dead band, noisy sensors flap at the threshold — the
 * classic LM393-without-hysteresis problem in software form. */
#ifndef HYSTERESIS_H
#define HYSTERESIS_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int32_t low;
    int32_t high;
    bool active;
} hysteresis_t;

void hysteresis_init(hysteresis_t *h, int32_t low, int32_t high);
/* feed a scaled engineering value; returns true when the ACTIVE edge
 * happens on this sample */
bool hysteresis_step(hysteresis_t *h, int32_t value);
bool hysteresis_state(const hysteresis_t *h);

#endif
