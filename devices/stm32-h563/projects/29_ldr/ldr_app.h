/* ldr_app.h — LDR light-level threshold events.
 * Composition: analog_in device + hysteresis primitive on RAW ADC counts.
 * Raw-count thresholds are deliberate: uniform across modules, independent
 * of scaling config, and the noise-flap immunity is what matters. */
#ifndef LDR_APP_H
#define LDR_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../lib/hysteresis.h"

/* 12-bit ADC: low 40%, high 60% of full scale */
#define LDR_LOW_COUNT   1638L
#define LDR_HIGH_COUNT  2457L

typedef struct {
    analog_in_t sensor;
    hysteresis_t threshold;
    uint32_t events;
} ldr_app_t;

void ldr_app_init(ldr_app_t *app, uint8_t channel);
/* one call per sample tick; returns true on a rising threshold crossing */
bool ldr_app_step(ldr_app_t *app);
uint16_t ldr_app_raw(ldr_app_t *app);
uint32_t ldr_app_events(const ldr_app_t *app);

#endif
