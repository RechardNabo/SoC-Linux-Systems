/* joystick_app.h — two-axis readout with direction classification.
 * Center deadzone is the contract: a resting stick must read NEUTRAL even
 * with real-world center offset; deflection beyond the zone classifies. */
#ifndef JOYSTICK_APP_H
#define JOYSTICK_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/analog_in/analog_in.h"
#include "../../drivers/devices/dig_in/dig_in.h"

#define JOYSTICK_CENTER_COUNT    2048L   /* half of 4095 */
#define JOYSTICK_DEADZONE_COUNT  600L

typedef enum {
    JOYSTICK_NEUTRAL = 0,
    JOYSTICK_UP, JOYSTICK_DOWN, JOYSTICK_LEFT, JOYSTICK_RIGHT
} joystick_direction_t;

/* pure classification — host-testable without any hardware */
joystick_direction_t joystick_classify(int32_t x_count, int32_t y_count);

typedef struct {
    analog_in_t axis_x;
    analog_in_t axis_y;
    dig_in_t button;
} joystick_app_t;

void joystick_app_init(joystick_app_t *app, uint8_t ch_x, uint8_t ch_y, uint8_t pin_btn);
joystick_direction_t joystick_app_step(joystick_app_t *app);
bool joystick_app_pressed(joystick_app_t *app);

#endif
