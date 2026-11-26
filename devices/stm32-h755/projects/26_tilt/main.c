/* main.c — kit module #26 Ball Tilt — standalone firmware, STM32H755.
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
    dig_in_t sensor;
    dig_in_config_t cfg = kit_dig_in_config(KIT_TILT, kit_default_pin(KIT_TILT));
    uint32_t events = 0U;
    bool was = false;
    dig_in_init(&sensor, &cfg);
    for (;;) {
        dig_in_sample(&sensor);
        if (dig_in_state(&sensor) && !was) events++;
        was = dig_in_state(&sensor);
    }
}
