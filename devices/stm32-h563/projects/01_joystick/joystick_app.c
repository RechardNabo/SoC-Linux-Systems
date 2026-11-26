#include "joystick_app.h"
#include "../../drivers/devices/kit/kit.h"

joystick_direction_t joystick_classify(int32_t x_count, int32_t y_count)
{
    const int32_t dx = x_count - JOYSTICK_CENTER_COUNT;
    const int32_t dy = y_count - JOYSTICK_CENTER_COUNT;
    const int32_t ax = dx < 0 ? -dx : dx;
    const int32_t ay = dy < 0 ? -dy : dy;
    if (ax < JOYSTICK_DEADZONE_COUNT && ay < JOYSTICK_DEADZONE_COUNT)
        return JOYSTICK_NEUTRAL;
    if (ax > ay) return dx > 0 ? JOYSTICK_RIGHT : JOYSTICK_LEFT;
    return dy > 0 ? JOYSTICK_DOWN : JOYSTICK_UP;
}

void joystick_app_init(joystick_app_t *app, uint8_t ch_x, uint8_t ch_y, uint8_t pin_btn)
{
    analog_in_config_t xc = kit_analog_config(KIT_JOYSTICK, ch_x);
    analog_in_config_t yc = kit_analog_config(KIT_JOYSTICK, ch_y);
    dig_in_config_t bc = kit_dig_in_config(KIT_JOYSTICK_BTN, pin_btn);
    analog_in_init(&app->axis_x, &xc);
    analog_in_init(&app->axis_y, &yc);
    dig_in_init(&app->button, &bc);
}

joystick_direction_t joystick_app_step(joystick_app_t *app)
{
    uint16_t x = 0U, y = 0U;
    (void)analog_in_read_raw(&app->axis_x, &x);
    (void)analog_in_read_raw(&app->axis_y, &y);
    return joystick_classify((int32_t)x, (int32_t)y);
}

bool joystick_app_pressed(joystick_app_t *app)
{
    dig_in_sample(&app->button);
    return dig_in_state(&app->button);
}
