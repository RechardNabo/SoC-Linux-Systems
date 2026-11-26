/* main.c — kit module #29 LDR — standalone firmware, STM32H755.
 * Super-loop over the device layer. Wiring/verification: README.md.
 * Build: STM32CubeIDE (HAL project provides clocks/init). Host-verified
 * logic: drivers/tests/unit/ (60 tests). */
#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/kit/kit.h"
#include "../../drivers/devices/pal/devpal.h"
#include "../../drivers/peripherals/adc/stm_adc.h"
#include "../../drivers/peripherals/tim/stm_tim.h"

#define LOOP_PAUSE  400000UL

int main(void)
{
    analog_in_t sensor;
    analog_in_config_t cfg = kit_analog_config(KIT_LDR, 0U);
    int32_t eng = 0;
    stm_adc_init();
    analog_in_init(&sensor, &cfg);
    for (;;) {
        analog_in_read_scaled(&sensor, &eng);   /* report over USART3 console */
    }
}
