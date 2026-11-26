/* main.c — kit module #12 RGB LED — standalone firmware, STM32H755.
 * Super-loop over the device layer. Wiring/verification: README.md.
 * Build: STM32CubeIDE (HAL project provides clocks/init). Host-verified
 * logic: drivers/tests/unit/ (60 tests). */
#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/kit/kit.h"
#include "../../drivers/devices/pal/devpal.h"
#include "../../drivers/peripherals/tim/stm_tim.h"

#define LOOP_PAUSE  400000UL

int main(void)
{
    rgb_led_t rgb;
    rgb_led_init(&rgb, 1U, 2U, 3U, 480000000UL, 1000UL);   /* TIM2 ch1/2/3 on PA5/6/7 */
    uint16_t hue = 0U;
    for (;;) {
        const uint16_t h = hue % 768U;
        uint8_t r, g, b;
        if (h < 256U)      { r = (uint8_t)(255U - h); g = (uint8_t)h; b = 0U; }
        else if (h < 512U) { r = 0U; g = (uint8_t)(511U - h); b = (uint8_t)(h - 256U); }
        else               { r = (uint8_t)(h - 512U); g = 0U; b = (uint8_t)(767U - h); }
        rgb_led_set(&rgb, r, g, b);
        hue++;
    }
}
