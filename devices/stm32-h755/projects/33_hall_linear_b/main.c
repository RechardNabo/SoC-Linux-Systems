/* main.c — Hall Linear B threshold monitor. Binding only — logic in hall_linear_b_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in hall_linear_b_app.c and is pinned by the
 * project's 3 host tests (see test_hall_linear_b_app.c, run: cd projects && make). */
#include <stdint.h>
#include "hall_linear_b_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    hall_linear_b_app_t app;
    hall_linear_b_app_init(&app, 0U);
    for (;;) {
        if (hall_linear_b_app_step(&app)) {
            /* threshold event — hook alarm/LED here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
