#include "broken_light_app.h"
#include "../../drivers/devices/kit/kit.h"

void broken_light_app_init(broken_light_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_BROKEN_LIGHT, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool broken_light_app_step(broken_light_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t broken_light_app_events(const broken_light_app_t *app) { return app->events; }
bool broken_light_app_active(broken_light_app_t *app) { return dig_in_state(&app->sensor); }
