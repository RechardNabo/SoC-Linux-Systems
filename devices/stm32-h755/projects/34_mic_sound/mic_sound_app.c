#include "mic_sound_app.h"
#include "../../drivers/devices/kit/kit.h"

void mic_sound_app_init(mic_sound_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_MIC_SOUND, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool mic_sound_app_step(mic_sound_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t mic_sound_app_events(const mic_sound_app_t *app) { return app->events; }
bool mic_sound_app_active(mic_sound_app_t *app) { return dig_in_state(&app->sensor); }
