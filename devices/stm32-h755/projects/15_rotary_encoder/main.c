/* main.c — Encoder as bounded 0-100 control with push-reset.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in rotary_encoder_app.c and is pinned by the
 * project's 3 host tests (see test_rotary_encoder_app.c, run: cd projects && make). */
#include <stdint.h>
#include "rotary_encoder_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    rotary_encoder_app_t app;
    rotary_encoder_app_init(&app, 6U, 7U, 8U);
    for (;;) {
        rotary_encoder_app_step(&app);
        /* position 0-100 — hook PWM/LED bar here on target */
    }
    return 0;
}
