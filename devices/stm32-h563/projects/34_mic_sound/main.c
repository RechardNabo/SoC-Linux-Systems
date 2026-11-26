/* main.c — Mic Sound event counter. Binding only — logic in mic_sound_app.c.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in mic_sound_app.c and is pinned by the
 * project's 3 host tests (see test_mic_sound_app.c, run: cd projects && make). */
#include <stdint.h>
#include "mic_sound_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    mic_sound_app_t app;
    mic_sound_app_init(&app, kit_default_pin(KIT_MIC_SOUND));
    for (;;) {
        if (mic_sound_app_step(&app)) {
            /* activation edge — hook LED/UART report here on target */
        }
        /* 10ms tick on target */
    }
    return 0;
}
