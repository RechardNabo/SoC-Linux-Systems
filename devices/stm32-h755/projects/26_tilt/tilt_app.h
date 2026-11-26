/* tilt_app.h — application logic for the tilt project.
 * Ball tilt activation counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef TILT_APP_H
#define TILT_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} tilt_app_t;

void tilt_app_init(tilt_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool tilt_app_step(tilt_app_t *app);
uint32_t tilt_app_events(const tilt_app_t *app);
bool tilt_app_active(tilt_app_t *app);

#endif
