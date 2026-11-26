/* main.c — Touch event counter. Binding only — logic in touch_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in touch_app.c and is pinned by the
 * project's 3 host tests (see test_touch_app.c, run: cd projects && make). */
#include <stdint.h>
#include "touch_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    touch_app_t app;
    touch_app_init(&app, kit_default_pin(KIT_TOUCH));
    for (;;) {
        if (touch_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
