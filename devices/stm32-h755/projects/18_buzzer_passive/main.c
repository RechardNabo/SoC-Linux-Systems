/* main.c — kit module #18 Passive Buzzer — standalone firmware, STM32H755.
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
    buzzer_t buzz;
    static const uint32_t scale[8] = { 262U, 294U, 330U, 349U, 392U, 440U, 494U, 523U };
    uint8_t note = 0U;
    uint32_t n = 0U;
    buzzer_init(&buzz, STM_TIM3, 1U, 480000000UL);   /* TIM3 ch1 — RGB TIM2 undisturbed */
    for (;;) {
        buzzer_tone(&buzz, scale[note]);
        note = (uint8_t)((note + 1U) % 8U);
        for (n = 0U; n < LOOP_PAUSE * 2U; n++) { }
    }
}
