/* main.c — Joystick direction reporter. Binding only — logic in joystick_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in joystick_app.c and is pinned by the
 * project's 3 host tests (see test_joystick_app.c, run: cd projects && make). */
#include <stdint.h>
#include "joystick_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    joystick_app_t app;
    joystick_app_init(&app, 0U, 1U, kit_default_pin(KIT_JOYSTICK_BTN));
    for (;;) {
        const joystick_direction_t dir = joystick_app_step(&app);
        if (dir != JOYSTICK_NEUTRAL) { /* direction hook: UART report on target */ }
        if (joystick_app_pressed(&app)) { /* select hook */ }
        /* 10ms tick on target */
    }
    return 0;
}
