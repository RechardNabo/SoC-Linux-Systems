/* sequencer.h — cyclic pattern sequencer: melodies, SOS, color scripts.
 * Pure logic: a table + position, wraps at the end. */
#ifndef SEQUENCER_H
#define SEQUENCER_H
#include <stdint.h>
#include <stddef.h>

typedef struct {
    const uint32_t *table;
    uint8_t length;
    uint8_t position;
} sequencer_t;

void sequencer_init(sequencer_t *s, const uint32_t *table, uint8_t length);
/* current element, then advance with wraparound */
uint32_t sequencer_next(sequencer_t *s);
uint8_t sequencer_position(const sequencer_t *s);

#endif
