/* pwm_out.h — PWM-output device class for RGB LED + passive buzzer, STM32H563.
 * Thin adaptation over the TIM-PWM peripheral driver: frequency lives in
 * the timer (shared per TIM), duty per channel. RGB shares TIM2 ch1/2/3;
 * the buzzer gets TIM3 ch1 so pitch retuning never disturbs color. */
#ifndef PWM_OUT_H
#define PWM_OUT_H

#include <stdint.h>
#include <stdbool.h>
#include "../../peripherals/tim/stm_tim.h"

typedef enum {
    PWM_OUT_STATUS_OK = 0,
    PWM_OUT_STATUS_INVALID_CONFIG,
    PWM_OUT_STATUS_INVALID_PARAM
} pwm_out_status_t;

typedef struct {
    stm_tim_channel_t tim;
    uint8_t channel;        /* 1-4 */
} pwm_out_channel_t;

typedef struct {
    pwm_out_channel_t r, g, b;
} rgb_led_t;

typedef struct {
    stm_tim_channel_t tim;
    uint8_t channel;
    uint32_t clk_hz;
    bool sounding;
} buzzer_t;

pwm_out_status_t pwm_out_init_channel(pwm_out_channel_t *ch, stm_tim_channel_t tim, uint8_t channel,
                                      uint32_t clk_hz, uint32_t frequency);
pwm_out_status_t pwm_out_set_permille(const pwm_out_channel_t *ch, uint32_t permille);

pwm_out_status_t rgb_led_init(rgb_led_t *dev, uint8_t r_ch, uint8_t g_ch, uint8_t b_ch,
                              uint32_t clk_hz, uint32_t frequency);
pwm_out_status_t rgb_led_set(rgb_led_t *dev, uint8_t red, uint8_t green, uint8_t blue);
pwm_out_status_t rgb_led_off(rgb_led_t *dev);

pwm_out_status_t buzzer_init(buzzer_t *dev, stm_tim_channel_t tim, uint8_t channel, uint32_t clk_hz);
pwm_out_status_t buzzer_tone(buzzer_t *dev, uint32_t frequency);
pwm_out_status_t buzzer_off(buzzer_t *dev);

#endif
