/* knock_app.h — application logic for the knock project.
 * Knock event counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef KNOCK_APP_H
#define KNOCK_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} knock_app_t;

void knock_app_init(knock_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool knock_app_step(knock_app_t *app);
uint32_t knock_app_events(const knock_app_t *app);
bool knock_app_active(knock_app_t *app);

#endif
