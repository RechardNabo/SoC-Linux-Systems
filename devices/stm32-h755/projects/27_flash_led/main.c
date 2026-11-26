/* main.c — Flash-LED power cycler.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in flash_led_app.c and is pinned by the
 * project's 3 host tests (see test_flash_led_app.c, run: cd projects && make). */
#include <stdint.h>
#include "flash_led_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    flash_led_app_t app;
    flash_led_app_init(&app, kit_default_pin(KIT_FLASH_LED));
    for (;;) {
        flash_led_app_step(&app);
        /* 10ms tick on target */
    }
    return 0;
}
