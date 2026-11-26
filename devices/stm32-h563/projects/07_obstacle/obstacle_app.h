/* obstacle_app.h — application logic for the obstacle project.
 * Obstacle sensor event counter.
 * Composition: dig_in device (debounce/polarity) + edge_count primitive
 * (one count per activation, never per hold). Hardware binding lives in
 * main.c — this module is pure composition and host-testable. */
#ifndef OBSTACLE_APP_H
#define OBSTACLE_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_in/dig_in.h"
#include "../lib/edge_count.h"

typedef struct {
    dig_in_t sensor;
    edge_count_t counter;
    uint32_t events;
} obstacle_app_t;

void obstacle_app_init(obstacle_app_t *app, uint8_t pin);
/* one call per sample tick; returns true on a NEW activation edge */
bool obstacle_app_step(obstacle_app_t *app);
uint32_t obstacle_app_events(const obstacle_app_t *app);
bool obstacle_app_active(obstacle_app_t *app);

#endif
