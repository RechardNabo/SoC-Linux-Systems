#include "flash_led_app.h"
#include "../../drivers/devices/kit/kit.h"

void flash_led_app_init(flash_led_app_t *app, uint8_t pin)
{
    dig_out_config_t cfg = kit_dig_out_config(KIT_FLASH_LED, pin);
    dig_out_init(&app->device, &cfg);   /* drives INACTIVE at power-on — the relay safety */
    blink_init(&app->cadence, FLASH_LED_HALF_PERIOD_TICKS);
}

void flash_led_app_step(flash_led_app_t *app)
{
    dig_out_set(&app->device, blink_step(&app->cadence));
}

bool flash_led_app_output(const flash_led_app_t *app)
{
    return dig_out_is_on(&app->device);
}
