/* touch_app.h — application logic for the touch project.
 * Capacitive touch event counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef TOUCH_APP_H
#define TOUCH_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} touch_app_t;

void touch_app_init(touch_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool touch_app_step(touch_app_t *app);
uint32_t touch_app_events(const touch_app_t *app);
bool touch_app_active(touch_app_t *app);

#endif
