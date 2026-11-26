/* main.c — Reed Rgb event counter. Binding only — logic in reed_rgb_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in reed_rgb_app.c and is pinned by the
 * project's 3 host tests (see test_reed_rgb_app.c, run: cd projects && make). */
#include <stdint.h>
#include "reed_rgb_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    reed_rgb_app_t app;
    reed_rgb_app_init(&app, kit_default_pin(KIT_REED_RGB));
    for (;;) {
        if (reed_rgb_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
