/* main.c — Flame event counter. Binding only — logic in flame_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in flame_app.c and is pinned by the
 * project's 3 host tests (see test_flame_app.c, run: cd projects && make). */
#include <stdint.h>
#include "flame_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    flame_app_t app;
    flame_app_init(&app, kit_default_pin(KIT_FLAME));
    for (;;) {
        if (flame_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
