#include "blink.h"

void blink_init(blink_t *b, uint32_t half_period_ticks)
{
    b->half_period_ticks = half_period_ticks;
    b->tick_count = 0U;
    b->level = false;          /* inactive first — outputs start safe */
    b->running = true;
}

bool blink_step(blink_t *b)
{
    if (!b->running) return false;
    if (++b->tick_count >= b->half_period_ticks) {
        b->tick_count = 0U;
        b->level = !b->level;
    }
    return b->level;
}

void blink_stop(blink_t *b)
{
    b->running = false;
    b->level = false;
}
