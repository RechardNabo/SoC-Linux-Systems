/* stm_hsem.h — hardware semaphore driver: the dual-core mutual-exclusion
 * primitive. Silicon semantics (RM0468):
 *   - 32 semaphores; each HSEM_Rx: LOCK bit31, COREID bits 11:8, PROCID 7:0
 *   - Take: write own COREID|PROCID|LOCK, read back — owned iff the
 *     read-back matches what was written (the write only sticks if free
 *     or already ours — this is the hardware race resolution)
 *   - Release: write COREID|PROCID WITHOUT the lock bit
 * The two-step write-then-verify is not optional ceremony: it IS the
 * arbitration. A driver that assumes the write always wins is broken. */
#ifndef STM_HSEM_H
#define STM_HSEM_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    STM_HSEM_STATUS_OK = 0,
    STM_HSEM_STATUS_INVALID_SEM,
    STM_HSEM_STATUS_BUSY,          /* owned by the other core/process */
    STM_HSEM_STATUS_NOT_OWNER      /* release attempted without ownership */
} stm_hsem_status_t;

#define STM_HSEM_COUNT   32U

stm_hsem_status_t stm_hsem_take(uint8_t sem, uint8_t procid, uint8_t coreid);
stm_hsem_status_t stm_hsem_release(uint8_t sem, uint8_t procid, uint8_t coreid);
bool stm_hsem_is_owner(uint8_t sem, uint8_t procid, uint8_t coreid);
/* owner inspection for diagnostics: returns packed COREID<<8|PROCID, 0 if free */
uint16_t stm_hsem_owner(uint8_t sem);

#endif
