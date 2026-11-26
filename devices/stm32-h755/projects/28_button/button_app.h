/* button_app.h — application logic for the button project.
 * Button press counter — debounced.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef BUTTON_APP_H
#define BUTTON_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} button_app_t;

void button_app_init(button_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool button_app_step(button_app_t *app);
uint32_t button_app_events(const button_app_t *app);
bool button_app_active(button_app_t *app);

#endif
