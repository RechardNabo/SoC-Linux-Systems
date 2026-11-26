#include "buzzer_active_app.h"

/* element = one 100ms tick: 1 on, 0 off. ...---... then a rest */
static const uint32_t sos[SOS_PATTERN_LENGTH] = {
    /* S: dot gap dot gap dot, then letter gap */
    1,0, 1,0, 1, 0,0,
    /* O: dash gap dash gap dash, then letter gap */
    1,1,1,0, 1,1,1,0, 1,1,1, 0,0,
    /* S again */
    1,0, 1,0, 1
};

const uint32_t *buzzer_active_app_pattern(void) { return sos; }

void buzzer_active_app_init(buzzer_active_app_t *app, uint8_t pin)
{
    dig_out_config_t cfg = { pin, DIG_OUT_ACTIVE_HIGH };
    dig_out_init(&app->buzzer, &cfg);
    sequencer_init(&app->pattern, sos, SOS_PATTERN_LENGTH);
    app->sounding = false;
}

void buzzer_active_app_step(buzzer_active_app_t *app)
{
    const uint32_t element = sequencer_next(&app->pattern);
    dig_out_set(&app->buzzer, element != 0U);
    app->sounding = element != 0U;
}

bool buzzer_active_app_sounding(const buzzer_active_app_t *app) { return app->sounding; }
uint8_t buzzer_active_app_position(const buzzer_active_app_t *app)
{
    return sequencer_position(&app->pattern);
}
