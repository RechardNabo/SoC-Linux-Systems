/* main.c — Strict red/green alternation — never both on.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in dual_led_app.c and is pinned by the
 * project's 3 host tests (see test_dual_led_app.c, run: cd projects && make). */
#include <stdint.h>
#include "dual_led_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    dual_led_app_t app;
    dual_led_app_init(&app, 14U, 15U);
    for (;;) {
        dual_led_app_step(&app);
        /* 10ms tick on target */
    }
    return 0;
}
