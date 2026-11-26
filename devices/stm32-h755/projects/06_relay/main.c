/* main.c — Relay click cadence — active-LOW power-on safety is the contract.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in relay_app.c and is pinned by the
 * project's 3 host tests (see test_relay_app.c, run: cd projects && make). */
#include <stdint.h>
#include "relay_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    relay_app_t app;
    relay_app_init(&app, kit_default_pin(KIT_RELAY));
    for (;;) {
        relay_app_step(&app);
        /* 10ms tick on target */
    }
    return 0;
}
