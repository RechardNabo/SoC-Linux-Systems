/* broken_light_app.h — application logic for the broken_light project.
 * Beam-break event counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef BROKEN_LIGHT_APP_H
#define BROKEN_LIGHT_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} broken_light_app_t;

void broken_light_app_init(broken_light_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool broken_light_app_step(broken_light_app_t *app);
uint32_t broken_light_app_events(const broken_light_app_t *app);
bool broken_light_app_active(broken_light_app_t *app);

#endif
