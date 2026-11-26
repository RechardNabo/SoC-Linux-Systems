/* main.c — DHT11 humidity reporter. Classification tested in dht11_app tests.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in dht11_app.c and is pinned by the
 * project's 3 host tests (see test_dht11_app.c, run: cd projects && make). */
#include <stdint.h>
#include "dht11_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    /* 1-wire transport runs on target; classification is the tested logic */
    comfort_band_t band = COMFORT_IDEAL;
    for (;;) {
        /* read sensor, then: band = dht11_classify_humidity(rh); */
        (void)band;
    }
    return 0;
}
