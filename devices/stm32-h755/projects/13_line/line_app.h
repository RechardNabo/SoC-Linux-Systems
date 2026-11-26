/* line_app.h — application logic for the line project.
 * Line sensor crossing counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef LINE_APP_H
#define LINE_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} line_app_t;

void line_app_init(line_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool line_app_step(line_app_t *app);
uint32_t line_app_events(const line_app_t *app);
bool line_app_active(line_app_t *app);

#endif
