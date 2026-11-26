/* heartbeat_app.h — PPG heartbeat counter.
 * Composition: analog_in + peak_detect primitive. The refractory period is
 * the honest contract: one heartbeat rings the sensor once, not three times. */
#ifndef HEARTBEAT_APP_H
#define HEARTBEAT_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../lib/peak_detect.h"

#define HEARTBEAT_THRESHOLD_COUNT   2250L   /* just above midscale */
#define HEARTBEAT_REFRACTORY_TICKS  30U     /* 300ms at 10ms sampling — max 200bpm */

typedef struct {
    analog_in_t sensor;
    peak_detect_t detector;
} heartbeat_app_t;

void heartbeat_app_init(heartbeat_app_t *app, uint8_t channel);
bool heartbeat_app_step(heartbeat_app_t *app);   /* true on a counted beat */
uint32_t heartbeat_app_beats(const heartbeat_app_t *app);

#endif
