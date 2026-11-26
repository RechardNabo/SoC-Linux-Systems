/* stm_i2c.c — see stm_i2c.h.
 * TIMINGR: SCLL bits 7:0, SCLH bits 15:8, SDADEL bits 19:16, SCLDEL
 * bits 23:20, PRESC bits 31:28. CR1: PE bit0. Fields are only writable
 * while PE=0 — the silicon enforces it, so the driver orders it. */
#include <xc.h>

#include "stm_i2c.h"
#include "../../bsp/stm_board.h"

#define CR1_PE  (1UL << 0)

typedef struct {
    volatile uint32_t *cr1, *timingr;
} stm_i2c_regs_t;

static stm_i2c_regs_t tbl[STM_I2C_CHANNEL_COUNT];
static int tbl_ready = 0;

static const stm_i2c_regs_t *regmap(stm_i2c_channel_t ch)
{
    if ((unsigned int)ch >= (unsigned int)STM_I2C_CHANNEL_COUNT) return 0;
    if (!tbl_ready) {
        tbl[STM_I2C1].cr1 = &I2C1CR1; tbl[STM_I2C1].timingr = &I2C1TIMINGR;
        tbl[STM_I2C2].cr1 = &I2C2CR1; tbl[STM_I2C2].timingr = &I2C2TIMINGR;
        tbl_ready = 1;
    }
    return &tbl[ch];
}

stm_i2c_status_t stm_i2c_compute_timing(uint32_t clk_hz, uint32_t clock_hz, stm_i2c_timing_t *out)
{
    /* reference-model approximation: pick presc so the remaining counts
     * fit their fields, split the period evenly minus fixed delays.
     * t_scl total = clk/clock; sync delays fixed at scldel=4 sdadel=2
     * (conservative analog-filter values); counts are value+1 encoded */
    uint32_t presc = 0U, total, half;
    if (out == 0 || clock_hz == 0U) return STM_I2C_STATUS_INVALID_PARAM;
    while (presc < 16U) {
        const uint32_t base = clk_hz / ((presc + 1U) * clock_hz);
        if (base >= 20U && base <= 2U * 256U + 12U) break;
        presc++;
    }
    if (presc >= 16U) return STM_I2C_STATUS_TIMING_IMPOSSIBLE;
    total = clk_hz / ((presc + 1U) * clock_hz);
    half = total / 2U;
    /* value+1 encoding; reserve margins covered by fixed delays */
    out->presc = presc;
    out->scldel = 4U;
    out->sdadel = 2U;
    out->sclh = (half > 1U) ? half - 1U : 1U;
    out->scll = (half > 1U) ? half - 1U : 1U;
    if (out->sclh > 255U || out->scll > 255U) return STM_I2C_STATUS_TIMING_IMPOSSIBLE;
    return STM_I2C_STATUS_OK;
}

uint32_t stm_i2c_pack_timingr(const stm_i2c_timing_t *t)
{
    return (t->scll & 0xFFUL)
         | ((t->sclh & 0xFFUL) << 8)
         | ((t->sdadel & 0xFUL) << 16)
         | ((t->scldel & 0xFUL) << 20)
         | ((t->presc & 0xFUL) << 28);
}

stm_i2c_status_t stm_i2c_init(stm_i2c_channel_t ch, const stm_i2c_config_t *config)
{
    const stm_i2c_regs_t *regs = regmap(ch);
    stm_i2c_timing_t t;
    stm_i2c_status_t st;
    if (regs == 0) return STM_I2C_STATUS_INVALID_CHANNEL;
    if (config == 0 || config->clk_hz == 0U) return STM_I2C_STATUS_INVALID_PARAM;
    st = stm_i2c_compute_timing(config->clk_hz, config->clock_hz, &t);
    if (st != STM_I2C_STATUS_OK) return st;

    *regs->cr1 = 0U;   /* PE clear — mandatory before touching TIMINGR */
    *regs->timingr = stm_i2c_pack_timingr(&t);
    *regs->cr1 = CR1_PE;   /* enable last */
    return STM_I2C_STATUS_OK;
}
