/* relay_app.h — Relay click cadence — active-LOW safety critical.
 * Composition: blink cadence primitive + dig_out device. The cadence is
 * the project's contract; the device polarity fact comes from the kit table. */
#ifndef RELAY_APP_H
#define RELAY_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_out/dig_out.h"
#include "../lib/blink.h"

#define RELAY_HALF_PERIOD_TICKS  200U

typedef struct {
    dig_out_t device;
    blink_t cadence;
} relay_app_t;

void relay_app_init(relay_app_t *app, uint8_t pin);
void relay_app_step(relay_app_t *app);   /* one call per tick */
bool relay_app_output(const relay_app_t *app);

#endif
