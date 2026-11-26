/* hall_switch_app.h — application logic for the hall_switch project.
 * Hall switch magnet events.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef HALL_SWITCH_APP_H
#define HALL_SWITCH_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} hall_switch_app_t;

void hall_switch_app_init(hall_switch_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool hall_switch_app_step(hall_switch_app_t *app);
uint32_t hall_switch_app_events(const hall_switch_app_t *app);
bool hall_switch_app_active(hall_switch_app_t *app);

#endif
