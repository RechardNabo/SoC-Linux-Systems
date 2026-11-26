/* rgb_led_app.h — continuous rainbow rotation (STM32: TIM PWM channels).
 * All three channels share TIM2 — field-preserving multi-channel config is
 * what the device layer fixed; this app depends on it. */
#ifndef RGB_LED_APP_H
#define RGB_LED_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/pwm_out/pwm_out.h"
#include "../lib/colorwheel.h"

typedef struct {
    rgb_led_t device;
    uint16_t hue;
} rgb_led_app_t;

void rgb_led_app_init(rgb_led_app_t *app, uint8_t r_ch, uint8_t g_ch, uint8_t b_ch,
                      uint32_t clk_hz, uint32_t freq);
void rgb_led_app_step(rgb_led_app_t *app);
uint16_t rgb_led_app_hue(const rgb_led_app_t *app);

#endif
