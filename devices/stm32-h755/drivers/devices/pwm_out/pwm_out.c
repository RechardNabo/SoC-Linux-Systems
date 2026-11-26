/* pwm_out.c — see pwm_out.h. The frequency/resolution interlock is absorbed
 * by the TIM solver — impossible frequencies come back as status codes. */
#include "pwm_out.h"

pwm_out_status_t pwm_out_init_channel(pwm_out_channel_t *ch, stm_tim_channel_t tim, uint8_t channel,
                                      uint32_t clk_hz, uint32_t frequency)
{
    stm_tim_config_t cfg;
    if (ch == 0) return PWM_OUT_STATUS_INVALID_CONFIG;
    cfg.clk_hz = clk_hz;
    cfg.frequency = frequency;
    if (stm_tim_pwm_init(tim, channel, &cfg) != STM_TIM_STATUS_OK) return PWM_OUT_STATUS_INVALID_CONFIG;
    ch->tim = tim;
    ch->channel = channel;
    return PWM_OUT_STATUS_OK;
}

pwm_out_status_t pwm_out_set_permille(const pwm_out_channel_t *ch, uint32_t permille)
{
    if (ch == 0 || permille > 1000U) return PWM_OUT_STATUS_INVALID_PARAM;
    if (stm_tim_set_duty_permille(ch->tim, ch->channel, permille) != STM_TIM_STATUS_OK)
        return PWM_OUT_STATUS_INVALID_CONFIG;
    return PWM_OUT_STATUS_OK;
}

pwm_out_status_t rgb_led_init(rgb_led_t *dev, uint8_t r_ch, uint8_t g_ch, uint8_t b_ch,
                              uint32_t clk_hz, uint32_t frequency)
{
    if (dev == 0) return PWM_OUT_STATUS_INVALID_CONFIG;
    /* all three on TIM2 — same frequency, independent duty */
    if (pwm_out_init_channel(&dev->r, STM_TIM2, r_ch, clk_hz, frequency) != PWM_OUT_STATUS_OK)
        return PWM_OUT_STATUS_INVALID_CONFIG;
    if (pwm_out_init_channel(&dev->g, STM_TIM2, g_ch, clk_hz, frequency) != PWM_OUT_STATUS_OK)
        return PWM_OUT_STATUS_INVALID_CONFIG;
    if (pwm_out_init_channel(&dev->b, STM_TIM2, b_ch, clk_hz, frequency) != PWM_OUT_STATUS_OK)
        return PWM_OUT_STATUS_INVALID_CONFIG;
    return rgb_led_off(dev);
}

pwm_out_status_t rgb_led_set(rgb_led_t *dev, uint8_t red, uint8_t green, uint8_t blue)
{
    if (dev == 0) return PWM_OUT_STATUS_INVALID_CONFIG;
    pwm_out_set_permille(&dev->r, ((uint32_t)red * 1000UL) / 255UL);
    pwm_out_set_permille(&dev->g, ((uint32_t)green * 1000UL) / 255UL);
    pwm_out_set_permille(&dev->b, ((uint32_t)blue * 1000UL) / 255UL);
    return PWM_OUT_STATUS_OK;
}

pwm_out_status_t rgb_led_off(rgb_led_t *dev)
{
    return rgb_led_set(dev, 0U, 0U, 0U);
}

pwm_out_status_t buzzer_init(buzzer_t *dev, stm_tim_channel_t tim, uint8_t channel, uint32_t clk_hz)
{
    pwm_out_channel_t tmp;
    if (dev == 0) return PWM_OUT_STATUS_INVALID_CONFIG;
    if (pwm_out_init_channel(&tmp, tim, channel, clk_hz, 2000UL) != PWM_OUT_STATUS_OK)
        return PWM_OUT_STATUS_INVALID_CONFIG;
    dev->tim = tim;
    dev->channel = channel;
    dev->clk_hz = clk_hz;
    dev->sounding = false;
    pwm_out_set_permille(&tmp, 0U);
    return PWM_OUT_STATUS_OK;
}

pwm_out_status_t buzzer_tone(buzzer_t *dev, uint32_t frequency)
{
    pwm_out_channel_t tmp;
    if (dev == 0 || frequency == 0U) return PWM_OUT_STATUS_INVALID_PARAM;
    /* retune: re-init the timer at the new frequency, then 50% duty */
    if (pwm_out_init_channel(&tmp, dev->tim, dev->channel, dev->clk_hz, frequency) != PWM_OUT_STATUS_OK)
        return PWM_OUT_STATUS_INVALID_PARAM;
    pwm_out_set_permille(&tmp, 500U);
    dev->sounding = true;
    return PWM_OUT_STATUS_OK;
}

pwm_out_status_t buzzer_off(buzzer_t *dev)
{
    pwm_out_channel_t tmp;
    if (dev == 0) return PWM_OUT_STATUS_INVALID_CONFIG;
    tmp.tim = dev->tim;
    tmp.channel = dev->channel;
    pwm_out_set_permille(&tmp, 0U);
    dev->sounding = false;
    return PWM_OUT_STATUS_OK;
}
