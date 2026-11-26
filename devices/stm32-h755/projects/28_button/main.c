/* main.c — Button event counter. Binding only — logic in button_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in button_app.c and is pinned by the
 * project's 3 host tests (see test_button_app.c, run: cd projects && make). */
#include <stdint.h>
#include "button_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    button_app_t app;
    button_app_init(&app, kit_default_pin(KIT_BUTTON));
    for (;;) {
        if (button_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
