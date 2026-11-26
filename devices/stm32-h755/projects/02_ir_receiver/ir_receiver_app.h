/* ir_receiver_app.h — HONEST STUB. NEC decoding needs edge-timestamp
 * capture (PIO on RP2040) which is not yet implemented. This module pins
 * the unsupported contract so the project fails loudly, not silently. */
#ifndef IR_RECEIVER_APP_H
#define IR_RECEIVER_APP_H

#include <stdbool.h>

typedef enum {
    IR_STATUS_UNSUPPORTED = 0
} ir_receiver_status_t;

static inline bool ir_receiver_supported(void) { return false; }
static inline ir_receiver_status_t ir_receiver_init_status(void) { return IR_STATUS_UNSUPPORTED; }
static inline int ir_receiver_decode(int edges) { (void)edges; return -1; }

#endif
