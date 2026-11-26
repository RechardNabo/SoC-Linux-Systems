#include "hall_linear_b_app.h"
#include "../../drivers/devices/kit/kit.h"

void hall_linear_b_app_init(hall_linear_b_app_t *app, uint8_t channel)
{
    analog_in_config_t cfg = kit_analog_config(KIT_HALL_LINEAR_B, channel);
    analog_in_init(&app->sensor, &cfg);
    hysteresis_init(&app->threshold, HALL_LINEAR_B_LOW_COUNT, HALL_LINEAR_B_HIGH_COUNT);
    app->events = 0U;
}

bool hall_linear_b_app_step(hall_linear_b_app_t *app)
{
    uint16_t raw = 0U;
    if (analog_in_read_raw(&app->sensor, &raw) != ANALOG_IN_STATUS_OK) return false;
    if (hysteresis_step(&app->threshold, (int32_t)raw)) {
        app->events++;
        return true;
    }
    return false;
}

uint16_t hall_linear_b_app_raw(hall_linear_b_app_t *app)
{
    uint16_t raw = 0U;
    (void)analog_in_read_raw(&app->sensor, &raw);
    return raw;
}

uint32_t hall_linear_b_app_events(const hall_linear_b_app_t *app) { return app->events; }
