/* sound_analog_app.h — sound-envelope loudness events.
 * Composition: analog_in device + hysteresis primitive on RAW ADC counts.
 * Raw-count thresholds are deliberate: uniform across modules, independent
 * of scaling config, and the noise-flap immunity is what matters. */
#ifndef SOUND_ANALOG_APP_H
#define SOUND_ANALOG_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../lib/hysteresis.h"

/* 12-bit ADC: low 40%, high 60% of full scale */
#define SOUND_ANALOG_LOW_COUNT   1638L
#define SOUND_ANALOG_HIGH_COUNT  2457L

typedef struct {
    analog_in_t sensor;
    hysteresis_t threshold;
    uint32_t events;
} sound_analog_app_t;

void sound_analog_app_init(sound_analog_app_t *app, uint8_t channel);
/* one call per sample tick; returns true on a rising threshold crossing */
bool sound_analog_app_step(sound_analog_app_t *app);
uint16_t sound_analog_app_raw(sound_analog_app_t *app);
uint32_t sound_analog_app_events(const sound_analog_app_t *app);

#endif
