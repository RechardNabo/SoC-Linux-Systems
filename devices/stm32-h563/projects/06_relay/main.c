/* main.c — kit module #6 5V Relay — standalone firmware, STM32H563.
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
    dig_out_t relay;
    dig_out_config_t cfg = kit_dig_out_config(KIT_RELAY, kit_default_pin(KIT_RELAY));  /* ACTIVE-LOW baked in */
    uint32_t n = 0U;
    dig_out_init(&relay, &cfg);   /* coil guaranteed OFF from power-on */
    for (;;) {
        dig_out_toggle(&relay);
        for (n = 0U; n < LOOP_PAUSE * 4U; n++) { }
    }
}
