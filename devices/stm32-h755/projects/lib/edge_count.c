#include "edge_count.h"

void edge_count_init(edge_count_t *ec)
{
    ec->edges = 0U;
    ec->last_active = false;
}

bool edge_count_step(edge_count_t *ec, bool active)
{
    const bool rising = active && !ec->last_active;
    ec->last_active = active;
    if (rising) ec->edges++;
    return rising;
}
