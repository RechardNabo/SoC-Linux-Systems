/* main.c — kit module #16 Active Buzzer — standalone firmware, STM32H563.
 * Super-loop over the device layer. Wiring/verification: README.md.
 * Build: STM32CubeIDE (HAL project provides clocks/init). Host-verified
 * logic: drivers/tests/unit/ (52 tests). */
#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/kit/kit.h"
#include "../../drivers/devices/pal/devpal.h"

#define LOOP_PAUSE  400000UL

int main(void)
{
    dig_out_t dev;
    dig_out_config_t cfg = kit_dig_out_config(KIT_BUZZER_ACTIVE, kit_default_pin(KIT_BUZZER_ACTIVE));
    uint32_t n = 0U;
    dig_out_init(&dev, &cfg);
    for (;;) {
        dig_out_toggle(&dev);
        for (n = 0U; n < LOOP_PAUSE; n++) { }
    }
}
