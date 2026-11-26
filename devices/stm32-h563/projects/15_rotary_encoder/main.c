/* main.c — kit module #15 KY-040 Encoder — standalone firmware, STM32H563.
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
    quad_enc_t enc;
    quad_enc_config_t ecfg = { DEVPAL_PIN(STM_PORTB, 8), DEVPAL_PIN(STM_PORTB, 9), 1 };
    int32_t last = 0;
    quad_enc_init(&enc, &ecfg);
    for (;;) {
        quad_enc_sample(&enc);
        if (quad_enc_detents(&enc) != last) {
            last = quad_enc_detents(&enc);   /* report over USART3 console */
        }
    }
}
