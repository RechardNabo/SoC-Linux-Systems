/* main.c — Magic Cup threshold monitor. Binding only — logic in magic_cup_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in magic_cup_app.c and is pinned by the
 * project's 3 host tests (see test_magic_cup_app.c, run: cd projects && make). */
#include <stdint.h>
#include "magic_cup_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    magic_cup_app_t app;
    magic_cup_app_init(&app, 0U);
    for (;;) {
        if (magic_cup_app_step(&app)) {
            /* threshold event — hook alarm/LED here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
