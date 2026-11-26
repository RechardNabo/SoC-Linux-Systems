#include "lm35_app.h"
#include "../../drivers/devices/kit/kit.h"

void lm35_app_init(lm35_app_t *app, uint8_t channel)
{
    analog_in_config_t cfg = kit_analog_config(KIT_LM35, channel);
    analog_in_init(&app->sensor, &cfg);
    hysteresis_init(&app->threshold, LM35_LOW_COUNT, LM35_HIGH_COUNT);
    app->events = 0U;
}

bool lm35_app_step(lm35_app_t *app)
{
    uint16_t raw = 0U;
    if (analog_in_read_raw(&app->sensor, &raw) != ANALOG_IN_STATUS_OK) return false;
    if (hysteresis_step(&app->threshold, (int32_t)raw)) {
        app->events++;
        return true;
    }
    return false;
}

uint16_t lm35_app_raw(lm35_app_t *app)
{
    uint16_t raw = 0U;
    (void)analog_in_read_raw(&app->sensor, &raw);
    return raw;
}

uint32_t lm35_app_events(const lm35_app_t *app) { return app->events; }
