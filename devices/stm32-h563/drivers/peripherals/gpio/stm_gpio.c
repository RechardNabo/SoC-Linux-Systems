/* stm_gpio.c — MODER bits 2n+1:2n (01=GP output, 00=input); BSRR low
 * halfword sets, high halfword resets — write-only atomic, no read needed. */
#include <xc.h>

#include "stm_gpio.h"

#define MODER_MASK(pin)  (3UL << ((pin) * 2U))
#define MODER_OUTPUT(pin) (1UL << ((pin) * 2U))

typedef struct {
    volatile uint32_t *moder, *idr, *odr, *bsrr;
} stm_gpio_regs_t;

static stm_gpio_regs_t tbl[STM_PORT_COUNT];
static int tbl_ready = 0;

static const stm_gpio_regs_t *regmap(stm_port_t port)
{
    if (!tbl_ready) {
        volatile uint32_t *moders[STM_PORT_COUNT] = {
            &GPIOA_MODER, &GPIOB_MODER, &GPIOC_MODER, &GPIOD_MODER,
            &GPIOE_MODER, &GPIOF_MODER, &GPIOG_MODER, &GPIOH_MODER };
        volatile uint32_t *idrs[STM_PORT_COUNT] = {
            &GPIOA_IDR, &GPIOB_IDR, &GPIOC_IDR, &GPIOD_IDR,
            &GPIOE_IDR, &GPIOF_IDR, &GPIOG_IDR, &GPIOH_IDR };
        volatile uint32_t *odrs[STM_PORT_COUNT] = {
            &GPIOA_ODR, &GPIOB_ODR, &GPIOC_ODR, &GPIOD_ODR,
            &GPIOE_ODR, &GPIOF_ODR, &GPIOG_ODR, &GPIOH_ODR };
        volatile uint32_t *bsrrs[STM_PORT_COUNT] = {
            &GPIOA_BSRR, &GPIOB_BSRR, &GPIOC_BSRR, &GPIOD_BSRR,
            &GPIOE_BSRR, &GPIOF_BSRR, &GPIOG_BSRR, &GPIOH_BSRR };
        int i;
        for (i = 0; i < (int)STM_PORT_COUNT; i++) {
            tbl[i].moder = moders[i]; tbl[i].idr = idrs[i];
            tbl[i].odr = odrs[i]; tbl[i].bsrr = bsrrs[i];
        }
        tbl_ready = 1;
    }
    return &tbl[port];
}

stm_gpio_status_t stm_gpio_set_output(stm_port_t port, uint8_t pin)
{
    const stm_gpio_regs_t *regs;
    if (!stm_gpio_valid(port, pin)) return STM_GPIO_STATUS_INVALID_PIN;
    regs = regmap(port);
    *regs->moder = (*regs->moder & ~MODER_MASK(pin)) | MODER_OUTPUT(pin);
    return STM_GPIO_STATUS_OK;
}

stm_gpio_status_t stm_gpio_set_input(stm_port_t port, uint8_t pin)
{
    const stm_gpio_regs_t *regs;
    if (!stm_gpio_valid(port, pin)) return STM_GPIO_STATUS_INVALID_PIN;
    regs = regmap(port);
    *regs->moder &= ~MODER_MASK(pin);
    return STM_GPIO_STATUS_OK;
}

stm_gpio_status_t stm_gpio_write(stm_port_t port, uint8_t pin, bool high)
{
    const stm_gpio_regs_t *regs;
    if (!stm_gpio_valid(port, pin)) return STM_GPIO_STATUS_INVALID_PIN;
    regs = regmap(port);
    /* atomic single-write: set in low halfword, reset in high */
    *regs->bsrr = high ? (1UL << pin) : (1UL << (pin + 16U));
    return STM_GPIO_STATUS_OK;
}

stm_gpio_status_t stm_gpio_toggle(stm_port_t port, uint8_t pin)
{
    const stm_gpio_regs_t *regs;
    if (!stm_gpio_valid(port, pin)) return STM_GPIO_STATUS_INVALID_PIN;
    regs = regmap(port);
    /* toggle needs the current state — read ODR, then one atomic BSRR write */
    volatile uint32_t live_odr;
    switch (port) {
        case STM_PORTA: live_odr = GPIOA_ODR; break;
        case STM_PORTB: live_odr = GPIOB_ODR; break;
        case STM_PORTC: live_odr = GPIOC_ODR; break;
        case STM_PORTD: live_odr = GPIOD_ODR; break;
        case STM_PORTE: live_odr = GPIOE_ODR; break;
        case STM_PORTF: live_odr = GPIOF_ODR; break;
        case STM_PORTG: live_odr = GPIOG_ODR; break;
        default:        live_odr = GPIOH_ODR; break;
    }
    if ((live_odr & (1UL << pin)) != 0U) *regs->bsrr = 1UL << (pin + 16U);
    else                                 *regs->bsrr = 1UL << pin;
    return STM_GPIO_STATUS_OK;
}

bool stm_gpio_read(stm_port_t port, uint8_t pin)
{
    if (!stm_gpio_valid(port, pin)) return false;
    return (*regmap(port)->idr & (1UL << pin)) != 0U;
}
