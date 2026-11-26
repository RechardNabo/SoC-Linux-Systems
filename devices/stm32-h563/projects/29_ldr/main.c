/* main.c — Ldr threshold monitor. Binding only — logic in ldr_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in ldr_app.c and is pinned by the
 * project's 3 host tests (see test_ldr_app.c, run: cd projects && make). */
#include <stdint.h>
#include "ldr_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    ldr_app_t app;
    ldr_app_init(&app, 0U);
    for (;;) {
        if (ldr_app_step(&app)) {
            /* threshold event — hook alarm/LED here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
