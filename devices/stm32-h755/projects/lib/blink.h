/* blink.h — cadence generator: the reusable heart of every blink/buzzer
 * pattern project. Pure logic: feed ticks, get output level. Non-blocking. */
#ifndef BLINK_H
#define BLINK_H
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t half_period_ticks;
    uint32_t tick_count;
    bool level;
    bool running;
} blink_t;

void blink_init(blink_t *b, uint32_t half_period_ticks);
/* call once per tick; returns the output level to drive */
bool blink_step(blink_t *b);
void blink_stop(blink_t *b);

#endif
