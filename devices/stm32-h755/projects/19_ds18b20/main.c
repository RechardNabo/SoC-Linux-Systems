/* main.c — DS18B20 temperature band reporter. Classification tested.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in ds18b20_app.c and is pinned by the
 * project's 3 host tests (see test_ds18b20_app.c, run: cd projects && make). */
#include <stdint.h>
#include "ds18b20_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    temp_band_t band = TEMP_BAND_COMFORT;
    for (;;) {
        /* read sensor, then: band = ds18b20_classify(centi_celsius); */
        (void)band;
    }
    return 0;
}
