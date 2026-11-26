/* main.c — Continuous rainbow rotation (STM32: TIM2 ch1/2/3).
 * Standalone flashable firmware; logic pinned by test_rgb_led_app.c. */
#include <stdint.h>
#include "rgb_led_app.h"
#include "../../drivers/devices/kit/kit.h"

#define CLK_HZ  250000000UL

int main(void)
{
    rgb_led_app_t app;
    rgb_led_app_init(&app, 1U, 2U, 3U, CLK_HZ, 1000U);
    for (;;) {
        rgb_led_app_step(&app);
        /* 10ms tick: full rainbow cycle in 7.7s */
    }
    return 0;
}
