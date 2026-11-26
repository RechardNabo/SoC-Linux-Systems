/* main.c — Obstacle event counter. Binding only — logic in obstacle_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in obstacle_app.c and is pinned by the
 * project's 3 host tests (see test_obstacle_app.c, run: cd projects && make). */
#include <stdint.h>
#include "obstacle_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    obstacle_app_t app;
    obstacle_app_init(&app, kit_default_pin(KIT_OBSTACLE));
    for (;;) {
        if (obstacle_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
