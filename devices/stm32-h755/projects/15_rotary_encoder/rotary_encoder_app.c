#include "rotary_encoder_app.h"

void rotary_encoder_app_init(rotary_encoder_app_t *app, uint8_t pin_a, uint8_t pin_b, uint8_t pin_btn)
{
    quad_enc_config_t ecfg = { pin_a, pin_b, 1 };
    dig_in_config_t bcfg = { pin_btn, DIG_IN_ACTIVE_LOW, 5U };
    quad_enc_init(&app->encoder, &ecfg);
    dig_in_init(&app->button, &bcfg);
    app->position = 0;
    app->last_detents = 0;
}

void rotary_encoder_app_step(rotary_encoder_app_t *app)
{
    int32_t detents, delta;
    quad_enc_sample(&app->encoder);
    dig_in_sample(&app->button);
    if (dig_in_state(&app->button)) {
        quad_enc_reset(&app->encoder);
        app->position = 0;
        app->last_detents = 0;
        return;
    }
    detents = quad_enc_detents(&app->encoder);
    delta = detents - app->last_detents;
    app->last_detents = detents;
    app->position += delta;
    if (app->position > 100) app->position = 100;
    if (app->position < 0)   app->position = 0;
}

int32_t rotary_encoder_app_position(const rotary_encoder_app_t *app) { return app->position; }
