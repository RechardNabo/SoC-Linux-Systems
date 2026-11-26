#include "sound_analog_app.h"
#include "../../drivers/devices/kit/kit.h"

void sound_analog_app_init(sound_analog_app_t *app, uint8_t channel)
{
    analog_in_config_t cfg = kit_analog_config(KIT_SOUND_ANALOG, channel);
    analog_in_init(&app->sensor, &cfg);
    hysteresis_init(&app->threshold, SOUND_ANALOG_LOW_COUNT, SOUND_ANALOG_HIGH_COUNT);
    app->events = 0U;
}

bool sound_analog_app_step(sound_analog_app_t *app)
{
    uint16_t raw = 0U;
    if (analog_in_read_raw(&app->sensor, &raw) != ANALOG_IN_STATUS_OK) return false;
    if (hysteresis_step(&app->threshold, (int32_t)raw)) {
        app->events++;
        return true;
    }
    return false;
}

uint16_t sound_analog_app_raw(sound_analog_app_t *app)
{
    uint16_t raw = 0U;
    (void)analog_in_read_raw(&app->sensor, &raw);
    return raw;
}

uint32_t sound_analog_app_events(const sound_analog_app_t *app) { return app->events; }
