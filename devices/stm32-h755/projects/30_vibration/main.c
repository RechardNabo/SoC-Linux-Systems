/* main.c — Vibration event counter. Binding only — logic in vibration_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in vibration_app.c and is pinned by the
 * project's 3 host tests (see test_vibration_app.c, run: cd projects && make). */
#include <stdint.h>
#include "vibration_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    vibration_app_t app;
    vibration_app_init(&app, kit_default_pin(KIT_VIBRATION));
    for (;;) {
        if (vibration_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
