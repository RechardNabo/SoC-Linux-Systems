/* lm35_b_app.h — second LM35 over-temperature alarm events.
 * Composition: analog_in device + hysteresis primitive on RAW ADC counts.
 * Raw-count thresholds are deliberate: uniform across modules, independent
 * of scaling config, and the noise-flap immunity is what matters. */
#ifndef LM35_B_APP_H
#define LM35_B_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../lib/hysteresis.h"

/* 12-bit ADC: low 40%, high 60% of full scale */
#define LM35_B_LOW_COUNT   1638L
#define LM35_B_HIGH_COUNT  2457L

typedef struct {
    analog_in_t sensor;
    hysteresis_t threshold;
    uint32_t events;
} lm35_b_app_t;

void lm35_b_app_init(lm35_b_app_t *app, uint8_t channel);
/* one call per sample tick; returns true on a rising threshold crossing */
bool lm35_b_app_step(lm35_b_app_t *app);
uint16_t lm35_b_app_raw(lm35_b_app_t *app);
uint32_t lm35_b_app_events(const lm35_b_app_t *app);

#endif
