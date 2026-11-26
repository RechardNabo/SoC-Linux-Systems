#include "hall_switch_app.h"
#include "../../drivers/devices/kit/kit.h"

void hall_switch_app_init(hall_switch_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_HALL_SWITCH, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool hall_switch_app_step(hall_switch_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t hall_switch_app_events(const hall_switch_app_t *app) { return app->events; }
bool hall_switch_app_active(hall_switch_app_t *app) { return dig_in_state(&app->sensor); }
