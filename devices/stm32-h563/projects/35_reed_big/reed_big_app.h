/* reed_big_app.h — application logic for the reed_big project.
 * Door open/close transition counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef REED_BIG_APP_H
#define REED_BIG_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} reed_big_app_t;

void reed_big_app_init(reed_big_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool reed_big_app_step(reed_big_app_t *app);
uint32_t reed_big_app_events(const reed_big_app_t *app);
bool reed_big_app_active(reed_big_app_t *app);

#endif
