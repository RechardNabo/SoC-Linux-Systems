/* mock_sfr.c — backing memory + BSRR behavioral model. */
#include <string.h>

#include "xc.h"

volatile uint32_t GPIOA_MODER, GPIOB_MODER, GPIOC_MODER, GPIOD_MODER;
volatile uint32_t GPIOE_MODER, GPIOF_MODER, GPIOG_MODER, GPIOH_MODER;
volatile uint32_t GPIOA_IDR, GPIOB_IDR, GPIOC_IDR, GPIOD_IDR;
volatile uint32_t GPIOE_IDR, GPIOF_IDR, GPIOG_IDR, GPIOH_IDR;
volatile uint32_t GPIOA_BSRR, GPIOB_BSRR, GPIOC_BSRR, GPIOD_BSRR;
volatile uint32_t GPIOE_BSRR, GPIOF_BSRR, GPIOG_BSRR, GPIOH_BSRR;

volatile uint32_t U1CR1, U1CR2, U1BRR, U1ISR, U1RDR, U1TDR;
volatile uint32_t U2CR1, U2CR2, U2BRR, U2ISR, U2RDR, U2TDR;
volatile uint32_t U3CR1, U3CR2, U3BRR, U3ISR, U3RDR, U3TDR;

volatile uint32_t SPI1CR1, SPI1CFG1, SPI1CFG2, SPI1SR, SPI1TXDR, SPI1RXDR;
volatile uint32_t SPI2CR1, SPI2CFG1, SPI2CFG2, SPI2SR, SPI2TXDR, SPI2RXDR;

volatile uint32_t I2C1CR1, I2C1TIMINGR;
volatile uint32_t I2C2CR1, I2C2TIMINGR;

volatile uint32_t TIM2CR1, TIM2EGR, TIM2PSC, TIM2ARR, TIM2CCMR1, TIM2CCER, TIM2CCR1, TIM2CCR2;
volatile uint32_t TIM3CR1, TIM3EGR, TIM3PSC, TIM3ARR, TIM3CCMR1, TIM3CCER, TIM3CCR1, TIM3CCR2;
volatile uint32_t TIM4CR1, TIM4EGR, TIM4PSC, TIM4ARR, TIM4CCMR1, TIM4CCER, TIM4CCR1, TIM4CCR2;
volatile uint32_t TIM5CR1, TIM5EGR, TIM5PSC, TIM5ARR, TIM5CCMR1, TIM5CCER, TIM5CCR1, TIM5CCR2;

static volatile uint32_t odr_store[8];

static volatile uint32_t *bsrr_for(int port)
{
    static volatile uint32_t *const all[8] = {
        &GPIOA_BSRR, &GPIOB_BSRR, &GPIOC_BSRR, &GPIOD_BSRR,
        &GPIOE_BSRR, &GPIOF_BSRR, &GPIOG_BSRR, &GPIOH_BSRR };
    return all[port];
}

volatile uint32_t *mock_odr(int port)
{
    volatile uint32_t *bsrr = bsrr_for(port);
    const uint32_t bits = *bsrr;
    odr_store[port] |= bits & 0xFFFFUL;           /* low halfword: set */
    odr_store[port] &= ~(bits >> 16);             /* high halfword: reset */
    *bsrr = 0U;                                   /* write-only: reads as 0 */
    return &odr_store[port];
}

void mock_sfr_reset(void)
{
    GPIOA_MODER = GPIOB_MODER = GPIOC_MODER = GPIOD_MODER = 0U;
    GPIOE_MODER = GPIOF_MODER = GPIOG_MODER = GPIOH_MODER = 0U;
    GPIOA_IDR = GPIOB_IDR = GPIOC_IDR = GPIOD_IDR = 0U;
    GPIOE_IDR = GPIOF_IDR = GPIOG_IDR = GPIOH_IDR = 0U;
    GPIOA_BSRR = GPIOB_BSRR = GPIOC_BSRR = GPIOD_BSRR = 0U;
    GPIOE_BSRR = GPIOF_BSRR = GPIOG_BSRR = GPIOH_BSRR = 0U;
    memset((void *)odr_store, 0, sizeof(odr_store));
    U1CR1 = U1CR2 = U1BRR = U1ISR = U1RDR = U1TDR = 0U;
    U2CR1 = U2CR2 = U2BRR = U2ISR = U2RDR = U2TDR = 0U;
    U3CR1 = U3CR2 = U3BRR = U3ISR = U3RDR = U3TDR = 0U;
    SPI1CR1 = SPI1CFG1 = SPI1CFG2 = SPI1SR = SPI1TXDR = SPI1RXDR = 0U;
    SPI2CR1 = SPI2CFG1 = SPI2CFG2 = SPI2SR = SPI2TXDR = SPI2RXDR = 0U;
    I2C1CR1 = I2C1TIMINGR = 0U;
    I2C2CR1 = I2C2TIMINGR = 0U;
    TIM2CR1 = TIM2EGR = TIM2PSC = TIM2ARR = TIM2CCMR1 = TIM2CCER = TIM2CCR1 = TIM2CCR2 = 0U;
    TIM3CR1 = TIM3EGR = TIM3PSC = TIM3ARR = TIM3CCMR1 = TIM3CCER = TIM3CCR1 = TIM3CCR2 = 0U;
    TIM4CR1 = TIM4EGR = TIM4PSC = TIM4ARR = TIM4CCMR1 = TIM4CCER = TIM4CCR1 = TIM4CCR2 = 0U;
    TIM5CR1 = TIM5EGR = TIM5PSC = TIM5ARR = TIM5CCMR1 = TIM5CCER = TIM5CCR1 = TIM5CCR2 = 0U;
}
