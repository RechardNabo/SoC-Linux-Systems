/* main.c — Mercury event counter. Binding only — logic in mercury_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in mercury_app.c and is pinned by the
 * project's 3 host tests (see test_mercury_app.c, run: cd projects && make). */
#include <stdint.h>
#include "mercury_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    mercury_app_t app;
    mercury_app_init(&app, kit_default_pin(KIT_MERCURY));
    for (;;) {
        if (mercury_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
