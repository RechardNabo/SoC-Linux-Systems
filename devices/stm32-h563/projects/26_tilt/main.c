/* main.c — Tilt event counter. Binding only — logic in tilt_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in tilt_app.c and is pinned by the
 * project's 3 host tests (see test_tilt_app.c, run: cd projects && make). */
#include <stdint.h>
#include "tilt_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    tilt_app_t app;
    tilt_app_init(&app, kit_default_pin(KIT_TILT));
    for (;;) {
        if (tilt_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
