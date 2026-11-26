/* main.c — Ir Proximity event counter. Binding only — logic in ir_proximity_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in ir_proximity_app.c and is pinned by the
 * project's 3 host tests (see test_ir_proximity_app.c, run: cd projects && make). */
#include <stdint.h>
#include "ir_proximity_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    ir_proximity_app_t app;
    ir_proximity_app_init(&app, kit_default_pin(KIT_IR_PROXIMITY));
    for (;;) {
        if (ir_proximity_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
