/* ir_proximity_app.h — application logic for the ir_proximity project.
 * IR proximity: counts object-detection events.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef IR_PROXIMITY_APP_H
#define IR_PROXIMITY_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} ir_proximity_app_t;

void ir_proximity_app_init(ir_proximity_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool ir_proximity_app_step(ir_proximity_app_t *app);
uint32_t ir_proximity_app_events(const ir_proximity_app_t *app);
bool ir_proximity_app_active(ir_proximity_app_t *app);

#endif
