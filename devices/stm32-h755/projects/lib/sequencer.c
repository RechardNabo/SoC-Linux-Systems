#include "sequencer.h"

void sequencer_init(sequencer_t *s, const uint32_t *table, uint8_t length)
{
    s->table = table;
    s->length = length;
    s->position = 0U;
}

uint32_t sequencer_next(sequencer_t *s)
{
    const uint32_t value = s->table[s->position];
    s->position = (uint8_t)((s->position + 1U) % s->length);
    return value;
}

uint8_t sequencer_position(const sequencer_t *s)
{
    return s->position;
}
