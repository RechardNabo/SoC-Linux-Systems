/* main.c — SOS pattern player.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in buzzer_active_app.c and is pinned by the
 * project's 3 host tests (see test_buzzer_active_app.c, run: cd projects && make). */
#include <stdint.h>
#include "buzzer_active_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    buzzer_active_app_t app;
    buzzer_active_app_init(&app, kit_default_pin(KIT_BUZZER_ACTIVE));
    for (;;) {
        buzzer_active_app_step(&app);
        /* 100ms tick on target */
    }
    return 0;
}
