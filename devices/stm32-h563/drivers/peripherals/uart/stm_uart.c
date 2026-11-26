/* stm_uart.c — see stm_uart.h.
 * CR1: UE bit0, RE bit2, TE bit3, PS bit9, PCE bit10, FIFOEN bit29.
 * CR2: STOP bits 13:12 (00=1bit, 10=2bit). ISR: RXNE bit5, TXE bit7. */
#include <xc.h>

#include "stm_uart.h"
#include "../../bsp/stm_board.h"

#define CR1_UE    (1UL << 0)
#define CR1_RE    (1UL << 2)
#define CR1_TE    (1UL << 3)
#define CR1_PS    (1UL << 9)
#define CR1_PCE   (1UL << 10)
#define CR2_STOP2 (2UL << 12)
#define ISR_RXNE  (1UL << 5)
#define ISR_TXE   (1UL << 7)

typedef struct {
    volatile uint32_t *cr1, *cr2, *brr, *isr, *rdr, *tdr;
} stm_uart_regs_t;

static stm_uart_regs_t tbl[STM_UART_CHANNEL_COUNT];
static int tbl_ready = 0;

static const stm_uart_regs_t *regmap(stm_uart_channel_t ch)
{
    if ((unsigned int)ch >= (unsigned int)STM_UART_CHANNEL_COUNT) return 0;
    if (!tbl_ready) {
        tbl[STM_USART1].cr1 = &U1CR1; tbl[STM_USART1].cr2 = &U1CR2;
        tbl[STM_USART1].brr = &U1BRR; tbl[STM_USART1].isr = &U1ISR;
        tbl[STM_USART1].rdr = &U1RDR; tbl[STM_USART1].tdr = &U1TDR;
        tbl[STM_USART2].cr1 = &U2CR1; tbl[STM_USART2].cr2 = &U2CR2;
        tbl[STM_USART2].brr = &U2BRR; tbl[STM_USART2].isr = &U2ISR;
        tbl[STM_USART2].rdr = &U2RDR; tbl[STM_USART2].tdr = &U2TDR;
        tbl[STM_USART3].cr1 = &U3CR1; tbl[STM_USART3].cr2 = &U3CR2;
        tbl[STM_USART3].brr = &U3BRR; tbl[STM_USART3].isr = &U3ISR;
        tbl[STM_USART3].rdr = &U3RDR; tbl[STM_USART3].tdr = &U3TDR;
        tbl_ready = 1;
    }
    return &tbl[ch];
}

stm_uart_status_t stm_uart_init(stm_uart_channel_t ch, const stm_uart_config_t *config)
{
    const stm_uart_regs_t *regs = regmap(ch);
    uint32_t brr, cr1;
    uint64_t actual_x1000, err_x1000;

    if (regs == 0) return STM_UART_STATUS_INVALID_CHANNEL;
    if (config == 0 || config->baud == 0U || config->clk_hz == 0U)
        return STM_UART_STATUS_INVALID_PARAM;

    /* BRR = clk/baud rounded nearest for oversampling-16 */
    brr = (uint32_t)((config->clk_hz + config->baud / 2U) / config->baud);
    if (brr < 16U || brr > 0xFFFFUL) return STM_UART_STATUS_INVALID_BAUD;

    actual_x1000 = ((uint64_t)config->clk_hz * 1000UL) / brr;
    err_x1000 = (actual_x1000 > config->baud * 1000UL)
        ? actual_x1000 - config->baud * 1000UL : config->baud * 1000UL - actual_x1000;
    if ((err_x1000 / config->baud) > STM_UART_ERR_LIMIT_X1000)
        return STM_UART_STATUS_INVALID_BAUD;

    /* config only writable while UE=0 — disable, configure, enable last */
    *regs->cr1 = 0U;
    *regs->cr2 = (config->stop_bits == 2U) ? CR2_STOP2 : 0U;
    *regs->brr = brr;
    cr1 = CR1_TE | CR1_RE;
    if (config->parity != STM_UART_PARITY_NONE) {
        cr1 |= CR1_PCE;
        if (config->parity == STM_UART_PARITY_ODD) cr1 |= CR1_PS;
    }
    *regs->cr1 = cr1 | CR1_UE;
    return STM_UART_STATUS_OK;
}

bool stm_uart_write_byte(stm_uart_channel_t ch, uint8_t byte)
{
    const stm_uart_regs_t *regs = regmap(ch);
    if (regs == 0) return false;
    if ((*regs->isr & ISR_TXE) == 0U) return false;
    *regs->tdr = byte;
    return true;
}

bool stm_uart_read_byte(stm_uart_channel_t ch, uint8_t *byte_out)
{
    const stm_uart_regs_t *regs = regmap(ch);
    if (regs == 0 || byte_out == 0) return false;
    if ((*regs->isr & ISR_RXNE) == 0U) return false;
    *byte_out = (uint8_t)(*regs->rdr & 0xFFU);
    return true;
}
