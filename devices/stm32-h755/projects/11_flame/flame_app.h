/* flame_app.h — application logic for the flame project.
 * Flame detection event counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef FLAME_APP_H
#define FLAME_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} flame_app_t;

void flame_app_init(flame_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool flame_app_step(flame_app_t *app);
uint32_t flame_app_events(const flame_app_t *app);
bool flame_app_active(flame_app_t *app);

#endif
