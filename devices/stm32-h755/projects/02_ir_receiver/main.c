/* main.c — IR receiver placeholder — UNSUPPORTED pending PIO capture. Fails loudly.
 * Standalone flashable firmware for this module. Hardware binding lives
 * here; ALL application logic lives in ir_receiver_app.c and is pinned by the
 * project's 3 host tests (see test_ir_receiver_app.c, run: cd projects && make). */
#include <stdint.h>
#include "ir_receiver_app.h"
#include "../../drivers/devices/kit/kit.h"

int main(void)
{
    if (!ir_receiver_supported()) {
        for (;;) { /* unsupported until PIO capture lands — see README */ }
    }
    return 0;
}
