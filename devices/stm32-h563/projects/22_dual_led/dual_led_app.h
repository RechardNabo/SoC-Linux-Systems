/* dual_led_app.h — strict red/green alternation: charge-status style.
 * The contract that matters: the two LEDs are NEVER on together. */
#ifndef DUAL_LED_APP_H
#define DUAL_LED_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_out/dig_out.h"
#include "../lib/blink.h"

typedef struct {
    dig_out_t red;
    dig_out_t green;
    blink_t cadence;
} dual_led_app_t;

void dual_led_app_init(dual_led_app_t *app, uint8_t red_pin, uint8_t green_pin);
void dual_led_app_step(dual_led_app_t *app);
bool dual_led_app_red_on(const dual_led_app_t *app);
bool dual_led_app_green_on(const dual_led_app_t *app);

#endif
