#include "magic_cup_app.h"
#include "../../drivers/devices/kit/kit.h"

void magic_cup_app_init(magic_cup_app_t *app, uint8_t channel)
{
    analog_in_config_t cfg = kit_analog_config(KIT_MAGIC_CUP, channel);
    analog_in_init(&app->sensor, &cfg);
    hysteresis_init(&app->threshold, MAGIC_CUP_LOW_COUNT, MAGIC_CUP_HIGH_COUNT);
    app->events = 0U;
}

bool magic_cup_app_step(magic_cup_app_t *app)
{
    uint16_t raw = 0U;
    if (analog_in_read_raw(&app->sensor, &raw) != ANALOG_IN_STATUS_OK) return false;
    if (hysteresis_step(&app->threshold, (int32_t)raw)) {
        app->events++;
        return true;
    }
    return false;
}

uint16_t magic_cup_app_raw(magic_cup_app_t *app)
{
    uint16_t raw = 0U;
    (void)analog_in_read_raw(&app->sensor, &raw);
    return raw;
}

uint32_t magic_cup_app_events(const magic_cup_app_t *app) { return app->events; }
