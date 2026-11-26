/* stm_spi.c — see stm_spi.h.
 * CFG1: DSIZE bits 4:0 (value-1: 7=8bit), MBR bits 30:28 (clk/2^(n+1)).
 * CFG2: MASTER bit22, CPHA bit24, CPOL bit25.
 * CR1: SPE bit0. SR: RXP bit0, TXP bit1. Layout per RM0481 — target
 * verification owed in the HIL phase, documented in README. */
#include <xc.h>

#include "stm_spi.h"
#include "../../bsp/stm_board.h"

#define CFG1_DSIZE8   (7UL << 0)
#define CFG1_MBR_SHIFT 28U
#define CFG2_MASTER   (1UL << 22)
#define CFG2_CPHA     (1UL << 24)
#define CFG2_CPOL     (1UL << 25)
#define CR1_SPE       (1UL << 0)
#define SR_RXP        (1UL << 0)
#define SR_TXP        (1UL << 1)

typedef struct {
    volatile uint32_t *cr1, *cfg1, *cfg2, *sr, *txdr, *rxdr;
} stm_spi_regs_t;

static stm_spi_regs_t tbl[STM_SPI_CHANNEL_COUNT];
static int tbl_ready = 0;

static const stm_spi_regs_t *regmap(stm_spi_channel_t ch)
{
    if ((unsigned int)ch >= (unsigned int)STM_SPI_CHANNEL_COUNT) return 0;
    if (!tbl_ready) {
        tbl[STM_SPI1].cr1 = &SPI1CR1; tbl[STM_SPI1].cfg1 = &SPI1CFG1;
        tbl[STM_SPI1].cfg2 = &SPI1CFG2; tbl[STM_SPI1].sr = &SPI1SR;
        tbl[STM_SPI1].txdr = &SPI1TXDR; tbl[STM_SPI1].rxdr = &SPI1RXDR;
        tbl[STM_SPI2].cr1 = &SPI2CR1; tbl[STM_SPI2].cfg1 = &SPI2CFG1;
        tbl[STM_SPI2].cfg2 = &SPI2CFG2; tbl[STM_SPI2].sr = &SPI2SR;
        tbl[STM_SPI2].txdr = &SPI2TXDR; tbl[STM_SPI2].rxdr = &SPI2RXDR;
        tbl_ready = 1;
    }
    return &tbl[ch];
}

uint32_t stm_spi_mbr(uint32_t clk_hz, uint32_t clock_hz)
{
    /* smallest n with clk/2^(n+1) <= target — never overclock */
    uint32_t n;
    for (n = 0U; n < 8U; n++) {
        if ((clk_hz >> (n + 1U)) <= clock_hz) return n;
    }
    return 7U;
}

uint32_t stm_spi_actual_clock(uint32_t clk_hz, uint32_t mbr)
{
    return clk_hz >> (mbr + 1U);
}

stm_spi_status_t stm_spi_init(stm_spi_channel_t ch, const stm_spi_config_t *config)
{
    const stm_spi_regs_t *regs = regmap(ch);
    uint32_t mbr, cfg2;
    if (regs == 0) return STM_SPI_STATUS_INVALID_CHANNEL;
    if (config == 0 || config->clock_hz == 0U || config->clk_hz == 0U)
        return STM_SPI_STATUS_INVALID_PARAM;
    mbr = stm_spi_mbr(config->clk_hz, config->clock_hz);

    cfg2 = CFG2_MASTER;
    if (config->mode == STM_SPI_MODE_1 || config->mode == STM_SPI_MODE_3) cfg2 |= CFG2_CPHA;
    if (config->mode == STM_SPI_MODE_2 || config->mode == STM_SPI_MODE_3) cfg2 |= CFG2_CPOL;

    *regs->cr1 = 0U;   /* SPE must be clear while configuring */
    *regs->cfg1 = CFG1_DSIZE8 | (mbr << CFG1_MBR_SHIFT);
    *regs->cfg2 = cfg2;
    *regs->cr1 = CR1_SPE;   /* enable last */
    return STM_SPI_STATUS_OK;
}

stm_spi_status_t stm_spi_exchange_byte(stm_spi_channel_t ch, uint8_t tx, uint8_t *rx_out)
{
    const stm_spi_regs_t *regs = regmap(ch);
    uint32_t spin = 100000UL;
    if (regs == 0) return STM_SPI_STATUS_INVALID_CHANNEL;
    while ((*regs->sr & SR_TXP) == 0U) {
        if (--spin == 0U) return STM_SPI_STATUS_TIMEOUT;
    }
    *regs->txdr = tx;
    spin = 100000UL;
    while ((*regs->sr & SR_RXP) == 0U) {
        if (--spin == 0U) return STM_SPI_STATUS_TIMEOUT;
    }
    if (rx_out != 0) *rx_out = (uint8_t)(*regs->rxdr & 0xFFU);
    return STM_SPI_STATUS_OK;
}
