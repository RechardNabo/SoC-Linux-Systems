/* stm_hsem.c — see stm_hsem.h. */
#include <xc.h>
#include "stm_hsem.h"

#define HSEM_LOCK_BIT   (1UL << 31)
#define COREID_SHIFT    8U

static volatile uint32_t *semreg(uint8_t sem)
{
    /* HSEM_R0..R31 — contiguous on silicon, indexed table in the mock */
    return &HSEM_R0 + sem;
}

static uint32_t pack(uint8_t procid, uint8_t coreid)
{
    return ((uint32_t)coreid << COREID_SHIFT) | procid;
}

stm_hsem_status_t stm_hsem_take(uint8_t sem, uint8_t procid, uint8_t coreid)
{
    volatile uint32_t *reg;
    if (sem >= STM_HSEM_COUNT) return STM_HSEM_STATUS_INVALID_SEM;
    reg = semreg(sem);
    /* pre-flight: locked by a foreign owner � don't even write. Silicon
     * arbitration in the write itself remains the backstop for the race
     * window between this read and the lock attempt; the read-back
     * verify below is what makes the race outcome visible. */
    {
        const uint32_t cur = *reg;
        if ((cur & HSEM_LOCK_BIT) != 0U && cur != (pack(procid, coreid) | HSEM_LOCK_BIT))
            return STM_HSEM_STATUS_BUSY;
    }
    /* step 1: attempt the lock */
    *reg = pack(procid, coreid) | HSEM_LOCK_BIT;
    /* step 2: verify — arbitration happens HERE, not in the write */
    if (*reg == (pack(procid, coreid) | HSEM_LOCK_BIT)) return STM_HSEM_STATUS_OK;
    return STM_HSEM_STATUS_BUSY;
}

stm_hsem_status_t stm_hsem_release(uint8_t sem, uint8_t procid, uint8_t coreid)
{
    volatile uint32_t *reg;
    if (sem >= STM_HSEM_COUNT) return STM_HSEM_STATUS_INVALID_SEM;
    if (!stm_hsem_is_owner(sem, procid, coreid)) return STM_HSEM_STATUS_NOT_OWNER;
    reg = semreg(sem);
    *reg = pack(procid, coreid);   /* no LOCK bit = release */
    return STM_HSEM_STATUS_OK;
}

bool stm_hsem_is_owner(uint8_t sem, uint8_t procid, uint8_t coreid)
{
    if (sem >= STM_HSEM_COUNT) return false;
    return *semreg(sem) == (pack(procid, coreid) | HSEM_LOCK_BIT);
}

uint16_t stm_hsem_owner(uint8_t sem)
{
    uint32_t v;
    if (sem >= STM_HSEM_COUNT) return 0U;
    v = *semreg(sem);
    if ((v & HSEM_LOCK_BIT) == 0U) return 0U;
    return (uint16_t)(v & 0xFFFFU);
}
