/* flash_led_app.h — Flash-LED power cycler: slow duty rotation.
 * Composition: blink cadence primitive + dig_out device. The cadence is
 * the project's contract; the device polarity fact comes from the kit table. */
#ifndef FLASH_LED_APP_H
#define FLASH_LED_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_out/dig_out.h"
#include "../lib/blink.h"

#define FLASH_LED_HALF_PERIOD_TICKS  100U

typedef struct {
    dig_out_t device;
    blink_t cadence;
} flash_led_app_t;

void flash_led_app_init(flash_led_app_t *app, uint8_t pin);
void flash_led_app_step(flash_led_app_t *app);   /* one call per tick */
bool flash_led_app_output(const flash_led_app_t *app);

#endif
