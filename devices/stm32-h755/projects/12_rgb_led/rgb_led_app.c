#include "rgb_led_app.h"

void rgb_led_app_init(rgb_led_app_t *app, uint8_t r_ch, uint8_t g_ch, uint8_t b_ch,
                      uint32_t clk_hz, uint32_t freq)
{
    rgb_led_init(&app->device, r_ch, g_ch, b_ch, clk_hz, freq);
    app->hue = 0U;
}

void rgb_led_app_step(rgb_led_app_t *app)
{
    uint8_t r, g, b;
    colorwheel_rgb(app->hue, &r, &g, &b);
    rgb_led_set(&app->device, r, g, b);
    app->hue = (uint16_t)((app->hue + 1U) % COLORWHEEL_STEPS);
}

uint16_t rgb_led_app_hue(const rgb_led_app_t *app) { return app->hue; }
