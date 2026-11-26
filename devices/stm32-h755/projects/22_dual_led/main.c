/* main.c — kit module #22 Dual LED — standalone firmware, STM32H755.
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
    dig_out_t red, green;
    dig_out_config_t rc = { DEVPAL_PIN(STM_PORTD, 3), DIG_OUT_ACTIVE_HIGH };
    dig_out_config_t gc = { DEVPAL_PIN(STM_PORTD, 4), DIG_OUT_ACTIVE_HIGH };
    bool phase = false;
    uint32_t n = 0U;
    dig_out_init(&red, &rc);
    dig_out_init(&green, &gc);
    for (;;) {
        phase = !phase;
        dig_out_set(&red, phase);
        dig_out_set(&green, !phase);
        for (n = 0U; n < LOOP_PAUSE; n++) { }
    }
}
