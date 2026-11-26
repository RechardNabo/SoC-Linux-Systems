/* main.c — Laser blinker 1Hz. Binding only — logic in laser_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in laser_app.c and is pinned by the
 * project's 3 host tests (see test_laser_app.c, run: cd projects && make). */
#include <stdint.h>
#include "laser_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    laser_app_t app;
    laser_app_init(&app, kit_default_pin(KIT_LASER));
    for (;;) {
        laser_app_step(&app);
        /* 10ms tick on target */
    }
    return 0;
}
