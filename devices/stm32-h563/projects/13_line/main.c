/* main.c — Line event counter. Binding only — logic in line_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in line_app.c and is pinned by the
 * project's 3 host tests (see test_line_app.c, run: cd projects && make). */
#include <stdint.h>
#include "line_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    line_app_t app;
    line_app_init(&app, kit_default_pin(KIT_LINE));
    for (;;) {
        if (line_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
