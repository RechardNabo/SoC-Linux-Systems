/* main.c — kit module #3 Laser Diode — standalone firmware, STM32H755.
 * Super-loop over the device layer. Wiring/verification: README.md.
 * Build: STM32CubeIDE (HAL project provides clocks/init). Host-verified
 * logic: drivers/tests/unit/ (60 tests). */
#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/kit/kit.h"
#include "../../drivers/devices/pal/devpal.h"

#define LOOP_PAUSE  400000UL

int main(void)
{
    dig_out_t dev;
    dig_out_config_t cfg = kit_dig_out_config(KIT_LASER, kit_default_pin(KIT_LASER));
    uint32_t n = 0U;
    dig_out_init(&dev, &cfg);
    for (;;) {
        dig_out_toggle(&dev);
        for (n = 0U; n < LOOP_PAUSE; n++) { }
    }
}
