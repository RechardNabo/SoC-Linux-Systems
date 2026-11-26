/* magic_cup_app.h — magic-cup tilt analog confirmation events.
 * Composition: analog_in device + hysteresis primitive on RAW ADC counts.
 * Raw-count thresholds are deliberate: uniform across modules, independent
 * of scaling config, and the noise-flap immunity is what matters. */
#ifndef MAGIC_CUP_APP_H
#define MAGIC_CUP_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../lib/hysteresis.h"

/* 12-bit ADC: low 40%, high 60% of full scale */
#define MAGIC_CUP_LOW_COUNT   1638L
#define MAGIC_CUP_HIGH_COUNT  2457L

typedef struct {
    analog_in_t sensor;
    hysteresis_t threshold;
    uint32_t events;
} magic_cup_app_t;

void magic_cup_app_init(magic_cup_app_t *app, uint8_t channel);
/* one call per sample tick; returns true on a rising threshold crossing */
bool magic_cup_app_step(magic_cup_app_t *app);
uint16_t magic_cup_app_raw(magic_cup_app_t *app);
uint32_t magic_cup_app_events(const magic_cup_app_t *app);

#endif
