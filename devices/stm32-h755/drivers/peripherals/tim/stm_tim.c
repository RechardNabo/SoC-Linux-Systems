/* stm_tim.c â€” see stm_tim.h.
 * CR1: CEN bit0. EGR: UG bit0 (load shadows). CCMR1: OC1M bits 6:4
 * (110=PWM mode1). CCER: CC1E bit0 (+4 per channel). CCR per channel. */
#include <xc.h>

#include "stm_tim.h"
#include "../../bsp/stm_board.h"

#define CR1_CEN    (1UL << 0)
#define EGR_UG     (1UL << 0)
#define CCMR_PWM1  (6UL << 4)

typedef struct {
    volatile uint32_t *cr1, *egr, *psc, *arr, *ccmr1, *ccmr2, *ccer, *ccr1, *ccr2, *ccr3, *ccr4;
} stm_tim_regs_t;

static stm_tim_regs_t tbl[STM_TIM_CHANNEL_COUNT];
static int tbl_ready = 0;

static const stm_tim_regs_t *regmap(stm_tim_channel_t tim)
{
    if ((unsigned int)tim >= (unsigned int)STM_TIM_CHANNEL_COUNT) return 0;
    if (!tbl_ready) {
        tbl[STM_TIM2].cr1 = &TIM2CR1; tbl[STM_TIM2].egr = &TIM2EGR;
        tbl[STM_TIM2].psc = &TIM2PSC; tbl[STM_TIM2].arr = &TIM2ARR;
        tbl[STM_TIM2].ccmr1 = &TIM2CCMR1; tbl[STM_TIM2].ccer = &TIM2CCER;
        tbl[STM_TIM2].ccmr2 = &TIM2CCMR2;
    tbl[STM_TIM2].ccr1 = &TIM2CCR1; tbl[STM_TIM2].ccr2 = &TIM2CCR2;
    tbl[STM_TIM2].ccr3 = &TIM2CCR3; tbl[STM_TIM2].ccr4 = &TIM2CCR4;
        tbl[STM_TIM3].cr1 = &TIM3CR1; tbl[STM_TIM3].egr = &TIM3EGR;
        tbl[STM_TIM3].psc = &TIM3PSC; tbl[STM_TIM3].arr = &TIM3ARR;
        tbl[STM_TIM3].ccmr1 = &TIM3CCMR1; tbl[STM_TIM3].ccer = &TIM3CCER;
        tbl[STM_TIM3].ccmr2 = &TIM3CCMR2;
    tbl[STM_TIM3].ccr1 = &TIM3CCR1; tbl[STM_TIM3].ccr2 = &TIM3CCR2;
    tbl[STM_TIM3].ccr3 = &TIM3CCR3; tbl[STM_TIM3].ccr4 = &TIM3CCR4;
        tbl[STM_TIM4].cr1 = &TIM4CR1; tbl[STM_TIM4].egr = &TIM4EGR;
        tbl[STM_TIM4].psc = &TIM4PSC; tbl[STM_TIM4].arr = &TIM4ARR;
        tbl[STM_TIM4].ccmr1 = &TIM4CCMR1; tbl[STM_TIM4].ccer = &TIM4CCER;
        tbl[STM_TIM4].ccmr2 = &TIM4CCMR2;
    tbl[STM_TIM4].ccr1 = &TIM4CCR1; tbl[STM_TIM4].ccr2 = &TIM4CCR2;
    tbl[STM_TIM4].ccr3 = &TIM4CCR3; tbl[STM_TIM4].ccr4 = &TIM4CCR4;
        tbl[STM_TIM5].cr1 = &TIM5CR1; tbl[STM_TIM5].egr = &TIM5EGR;
        tbl[STM_TIM5].psc = &TIM5PSC; tbl[STM_TIM5].arr = &TIM5ARR;
        tbl[STM_TIM5].ccmr1 = &TIM5CCMR1; tbl[STM_TIM5].ccer = &TIM5CCER;
        tbl[STM_TIM5].ccmr2 = &TIM5CCMR2;
    tbl[STM_TIM5].ccr1 = &TIM5CCR1; tbl[STM_TIM5].ccr2 = &TIM5CCR2;
    tbl[STM_TIM5].ccr3 = &TIM5CCR3; tbl[STM_TIM5].ccr4 = &TIM5CCR4;
        tbl_ready = 1;
    }
    return &tbl[tim];
}

bool stm_tim_solve(uint32_t clk_hz, uint32_t frequency, uint32_t *psc, uint32_t *arr)
{
    /* maximize resolution: smallest prescaler with arr fitting 32-bit
     * (TIM2/5 are 32-bit, TIM3/4 16-bit â€” solver reports 16-bit-safe values
     * so results work on all four timers in scope) */
    uint32_t total = clk_hz / frequency;
    if (frequency == 0U || total < 2U) return false;
    uint32_t p = 0U;
    while (p < 65536U) {
        const uint32_t a = total / (p + 1U);
        if (a >= 1U && a <= 65536U) {
            *psc = p;
            *arr = a - 1U;
            return true;
        }
        p++;
    }
    return false;
}

stm_tim_status_t stm_tim_pwm_init(stm_tim_channel_t tim, uint8_t channel, const stm_tim_config_t *config)
{
    const stm_tim_regs_t *regs = regmap(tim);
    uint32_t psc, arr;
    if (regs == 0) return STM_TIM_STATUS_INVALID_TIMER;
    if (config == 0 || channel < 1U || channel > 4U) return STM_TIM_STATUS_INVALID_PARAM;
    if (!stm_tim_solve(config->clk_hz, config->frequency, &psc, &arr))
        return STM_TIM_STATUS_FREQ_IMPOSSIBLE;

    volatile uint32_t *ccmr = (channel <= 2U) ? regs->ccmr1 : regs->ccmr2;
    const uint8_t field = (uint8_t)((channel - 1U) % 2U);   /* 0 = odd channel, 1 = even */
    *regs->cr1 = 0U;
    *regs->psc = psc;
    *regs->arr = arr;
    /* RMW — overwriting the whole register would clobber the sibling
     * channel's PWM mode. The RGB-on-one-timer use case exposed this. */
    *ccmr = (*ccmr & ~(0x7UL << (4U + field * 8U))) | (6UL << (4U + field * 8U));
    *regs->ccer |= 1UL << ((channel - 1U) * 4U);
    *regs->egr = EGR_UG;      /* load shadow registers */
    *regs->cr1 |= CR1_CEN;    /* enable — |= so a second channel on the same
                               * timer doesn't reset CR1 state */
    return STM_TIM_STATUS_OK;
}

stm_tim_status_t stm_tim_set_duty_permille(stm_tim_channel_t tim, uint8_t channel, uint32_t permille)
{
    const stm_tim_regs_t *regs = regmap(tim);
    uint32_t level;
    if (regs == 0) return STM_TIM_STATUS_INVALID_TIMER;
    if (permille > 1000U) return STM_TIM_STATUS_INVALID_PARAM;
    level = ((*regs->arr + 1UL) * permille) / 1000U;
    if (channel == 1U) *regs->ccr1 = level;
    else if (channel == 2U) *regs->ccr2 = level;
    else if (channel == 3U) *regs->ccr3 = level;
    else if (channel == 4U) *regs->ccr4 = level;
    else return STM_TIM_STATUS_INVALID_PARAM;
    return STM_TIM_STATUS_OK;
}
