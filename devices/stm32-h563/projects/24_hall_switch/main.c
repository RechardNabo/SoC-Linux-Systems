/* main.c — Hall Switch event counter. Binding only — logic in hall_switch_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in hall_switch_app.c and is pinned by the
 * project's 3 host tests (see test_hall_switch_app.c, run: cd projects && make). */
#include <stdint.h>
#include "hall_switch_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    hall_switch_app_t app;
    hall_switch_app_init(&app, kit_default_pin(KIT_HALL_SWITCH));
    for (;;) {
        if (hall_switch_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
