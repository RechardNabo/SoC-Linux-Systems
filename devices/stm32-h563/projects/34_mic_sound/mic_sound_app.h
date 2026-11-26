/* mic_sound_app.h — application logic for the mic_sound project.
 * Clap detection counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef MIC_SOUND_APP_H
#define MIC_SOUND_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} mic_sound_app_t;

void mic_sound_app_init(mic_sound_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool mic_sound_app_step(mic_sound_app_t *app);
uint32_t mic_sound_app_events(const mic_sound_app_t *app);
bool mic_sound_app_active(mic_sound_app_t *app);

#endif
