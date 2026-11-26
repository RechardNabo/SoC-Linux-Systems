/* hall_linear_app.h — linear-hall field-strength deviation events.
 * Composition: analog_in device + hysteresis primitive on RAW ADC counts.
 * Raw-count thresholds are deliberate: uniform across modules, independent
 * of scaling config, and the noise-flap immunity is what matters. */
#ifndef HALL_LINEAR_APP_H
#define HALL_LINEAR_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../lib/hysteresis.h"

/* 12-bit ADC: low 40%, high 60% of full scale */
#define HALL_LINEAR_LOW_COUNT   1638L
#define HALL_LINEAR_HIGH_COUNT  2457L

typedef struct {
    analog_in_t sensor;
    hysteresis_t threshold;
    uint32_t events;
} hall_linear_app_t;

void hall_linear_app_init(hall_linear_app_t *app, uint8_t channel);
/* one call per sample tick; returns true on a rising threshold crossing */
bool hall_linear_app_step(hall_linear_app_t *app);
uint16_t hall_linear_app_raw(hall_linear_app_t *app);
uint32_t hall_linear_app_events(const hall_linear_app_t *app);

#endif
