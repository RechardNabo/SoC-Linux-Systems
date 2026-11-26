/* main.c — Knock event counter. Binding only — logic in knock_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in knock_app.c and is pinned by the
 * project's 3 host tests (see test_knock_app.c, run: cd projects && make). */
#include <stdint.h>
#include "knock_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    knock_app_t app;
    knock_app_init(&app, kit_default_pin(KIT_KNOCK));
    for (;;) {
        if (knock_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
