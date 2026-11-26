/* main.c — Sound Analog threshold monitor. Binding only — logic in sound_analog_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in sound_analog_app.c and is pinned by the
 * project's 3 host tests (see test_sound_analog_app.c, run: cd projects && make). */
#include <stdint.h>
#include "sound_analog_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    sound_analog_app_t app;
    sound_analog_app_init(&app, 0U);
    for (;;) {
        if (sound_analog_app_step(&app)) {
            /* threshold event — hook alarm/LED here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
