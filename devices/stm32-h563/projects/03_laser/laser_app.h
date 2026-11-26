/* laser_app.h — Laser blinker: 1Hz 50% duty at a 10ms tick.
 * Composition: blink cadence primitive + dig_out device. The cadence is
 * the project's contract; the device polarity fact comes from the kit table. */
#ifndef LASER_APP_H
#define LASER_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_out/dig_out.h"
#include "../lib/blink.h"

#define LASER_HALF_PERIOD_TICKS  50U

typedef struct {
    dig_out_t device;
    blink_t cadence;
} laser_app_t;

void laser_app_init(laser_app_t *app, uint8_t pin);
void laser_app_step(laser_app_t *app);   /* one call per tick */
bool laser_app_output(const laser_app_t *app);

#endif
