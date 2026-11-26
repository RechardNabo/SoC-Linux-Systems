#include "ldr_app.h"
#include "../../drivers/devices/kit/kit.h"

void ldr_app_init(ldr_app_t *app, uint8_t channel)
{
    analog_in_config_t cfg = kit_analog_config(KIT_LDR, channel);
    analog_in_init(&app->sensor, &cfg);
    hysteresis_init(&app->threshold, LDR_LOW_COUNT, LDR_HIGH_COUNT);
    app->events = 0U;
}

bool ldr_app_step(ldr_app_t *app)
{
    uint16_t raw = 0U;
    if (analog_in_read_raw(&app->sensor, &raw) != ANALOG_IN_STATUS_OK) return false;
    if (hysteresis_step(&app->threshold, (int32_t)raw)) {
        app->events++;
        return true;
    }
    return false;
}

uint16_t ldr_app_raw(ldr_app_t *app)
{
    uint16_t raw = 0U;
    (void)analog_in_read_raw(&app->sensor, &raw);
    return raw;
}

uint32_t ldr_app_events(const ldr_app_t *app) { return app->events; }
