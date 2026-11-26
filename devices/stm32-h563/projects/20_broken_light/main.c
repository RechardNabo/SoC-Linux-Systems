/* main.c — Broken Light event counter. Binding only — logic in broken_light_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in broken_light_app.c and is pinned by the
 * project's 3 host tests (see test_broken_light_app.c, run: cd projects && make). */
#include <stdint.h>
#include "broken_light_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    broken_light_app_t app;
    broken_light_app_init(&app, kit_default_pin(KIT_BROKEN_LIGHT));
    for (;;) {
        if (broken_light_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
