/* stm_tim.h — general-purpose timer + PWM driver for STM32H5 (TIM2-5).
 * Update frequency = clk/((PSC+1)x(ARR+1)) — two cascaded dividers, both
 * value+1 encoded. PWM mode 1, channel duty via CCR. */
#ifndef STM_TIM_H
#define STM_TIM_H

#include <stdint.h>
#include <stdbool.h>

typedef enum { STM_TIM2 = 0, STM_TIM3, STM_TIM4, STM_TIM5, STM_TIM_CHANNEL_COUNT } stm_tim_channel_t;

typedef enum {
    STM_TIM_STATUS_OK = 0, STM_TIM_STATUS_INVALID_TIMER,
    STM_TIM_STATUS_INVALID_PARAM, STM_TIM_STATUS_FREQ_IMPOSSIBLE
} stm_tim_status_t;

typedef struct {
    uint32_t clk_hz;
    uint32_t frequency;   /* update/pwm frequency */
} stm_tim_config_t;

stm_tim_status_t stm_tim_pwm_init(stm_tim_channel_t tim, uint8_t channel, const stm_tim_config_t *config);
stm_tim_status_t stm_tim_set_duty_permille(stm_tim_channel_t tim, uint8_t channel, uint32_t permille);
/* PSC/ARR solver exposed for tests */
bool stm_tim_solve(uint32_t clk_hz, uint32_t frequency, uint32_t *psc, uint32_t *arr);

#endif
