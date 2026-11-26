/* main.c — Two-octave scale player (STM32: TIM3 ch1).
 * Standalone flashable firmware; logic pinned by test_buzzer_passive_app.c. */
#include <stdint.h>
#include "buzzer_passive_app.h"
#include "../../drivers/devices/kit/kit.h"

#define CLK_HZ  250000000UL

int main(void)
{
    buzzer_passive_app_t app;
    buzzer_passive_app_init(&app, 1U, CLK_HZ);
    for (;;) {
        buzzer_passive_app_step(&app);
        /* one note per 300ms tick on target */
    }
    return 0;
}
