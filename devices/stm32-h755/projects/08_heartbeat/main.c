/* main.c — Heartbeat counter with refractory-period honesty.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in heartbeat_app.c and is pinned by the
 * project's 3 host tests (see test_heartbeat_app.c, run: cd projects && make). */
#include <stdint.h>
#include "heartbeat_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    heartbeat_app_t app;
    heartbeat_app_init(&app, 0U);
    for (;;) {
        if (heartbeat_app_step(&app)) {
            /* beat counted — BPM = 6000 / ticks_between on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
