/* main.c — kit module #24 Hall Switch — standalone firmware, STM32H563.
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
    dig_in_t sensor;
    dig_in_config_t cfg = kit_dig_in_config(KIT_HALL_SWITCH, kit_default_pin(KIT_HALL_SWITCH));
    uint32_t events = 0U;
    bool was = false;
    dig_in_init(&sensor, &cfg);
    for (;;) {
        dig_in_sample(&sensor);
        if (dig_in_state(&sensor) && !was) events++;
        was = dig_in_state(&sensor);
    }
}
