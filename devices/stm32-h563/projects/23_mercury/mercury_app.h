/* mercury_app.h — application logic for the mercury project.
 * Mercury tilt activation counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef MERCURY_APP_H
#define MERCURY_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} mercury_app_t;

void mercury_app_init(mercury_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool mercury_app_step(mercury_app_t *app);
uint32_t mercury_app_events(const mercury_app_t *app);
bool mercury_app_active(mercury_app_t *app);

#endif
