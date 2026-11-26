/* edge_count.h — rising-edge event counter for digital-input projects.
 * An activation counts ONCE no matter how long it is held; the next count
 * requires a release first. That contract is what makes knock/vibration/
 * door sensors honest. */
#ifndef EDGE_COUNT_H
#define EDGE_COUNT_H
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t edges;
    bool last_active;
} edge_count_t;

void edge_count_init(edge_count_t *ec);
/* feed the debounced active state once per sample; returns true on the
 * sample where a NEW activation edge was counted */
bool edge_count_step(edge_count_t *ec, bool active);

#endif
