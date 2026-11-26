#include "dual_led_app.h"

void dual_led_app_init(dual_led_app_t *app, uint8_t red_pin, uint8_t green_pin)
{
    dig_out_config_t rc = { red_pin, DIG_OUT_ACTIVE_HIGH };
    dig_out_config_t gc = { green_pin, DIG_OUT_ACTIVE_HIGH };
    dig_out_init(&app->red, &rc);
    dig_out_init(&app->green, &gc);
    blink_init(&app->cadence, 50U);   /* 1Hz alternation at 10ms tick */
}

void dual_led_app_step(dual_led_app_t *app)
{
    const bool phase = blink_step(&app->cadence);
    dig_out_set(&app->red, phase);
    dig_out_set(&app->green, !phase);
}

bool dual_led_app_red_on(const dual_led_app_t *app)   { return dig_out_is_on(&app->red); }
bool dual_led_app_green_on(const dual_led_app_t *app) { return dig_out_is_on(&app->green); }
