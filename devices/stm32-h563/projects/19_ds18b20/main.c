/* main.c — kit module #19 DS18B20 — standalone firmware, STM32H563.
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

    for (;;) {
        /* PLACEHOLDER: needs the 1-wire/capture time engine —
         * honestly UNSUPPORTED on STM32H563 this pass; see kit.c */
    }
}
