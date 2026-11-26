/* main.c — Lm35 threshold monitor. Binding only — logic in lm35_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in lm35_app.c and is pinned by the
 * project's 3 host tests (see test_lm35_app.c, run: cd projects && make). */
#include <stdint.h>
#include "lm35_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    lm35_app_t app;
    lm35_app_init(&app, 0U);
    for (;;) {
        if (lm35_app_step(&app)) {
            /* threshold event — hook alarm/LED here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
